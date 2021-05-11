/*!< @encoding utf-8 */
/**
 * *****************************************************************************
 * @file         termux_api.c/h
 * @brief        api of termux
 * @author       tqfx
 * @date         20210101
 * @version      0.01
 * @copyright    Copyright (c) 2020-2021
 * *****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "termux_api.h"

/* Private includes ----------------------------------------------------------*/

#include "kstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

#define CMD_OP_ADD(_k_, _s_, _v_) \
    do                            \
    {                             \
        char *tmp = NULL;         \
        cmdstr(&tmp, _v_);        \
        (void)ksprintf(_k_,       \
                       " "_s_     \
                       " \"%s\"", \
                       tmp);      \
        PFREE(free, tmp);         \
    } while (0)

/* Private typedef -----------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void cmdstr(char **dst, const char *src);
static int  cmdout(const char *str);
static int  cmdsh(char **out, const char *str);

/* Private user code ---------------------------------------------------------*/

static void cmdstr(char **dst, const char *src)
{
    kstring_t *ks = ks_init();
    (void)kputs(src, ks);
    (void)ks_mod(ks, "\"", "\\\"");
    *dst = ks_release(ks);
    PFREE(free, ks);
}

static int cmdout(const char *str)
{
#ifdef CMD_SHOW
    (void)printf("%s\n", str);
#endif /* CMD_SHOW */
    FILE *pipe = popen(str, "r");
    if (!pipe)
    {
#ifdef CMD_SHOW
        perror(str);
#endif /* CMD_SHOW */
        return -1;
    }
    for (;;)
    {
#ifdef CMD_SHOW
        int tmp = fgetc(pipe);
#else
        (void)fgetc(pipe);
#endif /* CMD_SHOW */
        if (feof(pipe))
        {
            break;
        }
#ifdef CMD_SHOW
        (void)putchar(tmp);
#endif /* CMD_SHOW */
    }
    PFREE(pclose, pipe);
    return 0;
}

static int cmdsh(char **out, const char *str)
{
#ifdef CMD_SHOW
    (void)printf("%s\n", str);
#endif /* CMD_SHOW */
    FILE *pipe = popen(str, "r");
    if (pipe == NULL)
    {
#ifdef CMD_SHOW
        perror(str);
#endif /* CMD_SHOW */
        return -1;
    }
    kstring_t ks = {.l = 0U, .m = 1U};
    ks.s         = (char *)malloc(sizeof(char));
    for (;;)
    {
        int tmp = fgetc(pipe);
        if (feof(pipe))
        {
            break;
        }
        (void)kputc_(tmp, &ks);
    }
    (void)kputc_(0, &ks);
    PFREE(pclose, pipe);
#ifdef CMD_SHOW
    (void)printf("%s\n", ks.s);
#endif
    *out = ks_release(&ks);
    return 0;
}

/*termux-audio-info---------------------------------*/

int termux_audio_info(char **out)
{
    return cmdsh(out, "termux-audio-info");
}

/*termux-battery-status-----------------------------*/

int termux_battery_status(char **out)
{
    return cmdsh(out, "termux-battery-status");
}

/*termux-brightness-------------------------------*/

int termux_brightness(int num)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-brightness ");

    if (num > -1 && num < 256)
    {
        (void)ksprintf(ks, "%i", num);
    }
    else
    {
        (void)ksprintf(ks, "auto");
    }

    int ret = cmdout(ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*termux-call-log---------------------------------*/

int termux_call_log(char **out, int l, int o)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-call-log");

    if (l > 0)
    {
        (void)ksprintf(ks, " -l %i", l);
    }

    if (o > -1)
    {
        (void)ksprintf(ks, " -o %i", o);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*termux-camera-----------------------------------*/

int termux_camera_info(char **out)
{
    return cmdsh(out, "termux-camera-info");
}

int termux_camera_photo(const char *filename, unsigned int c)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-camera-photo -c %u", c);

    int ret = -1;

    if (filename)
    {
        CMD_OP_ADD(ks, "", filename);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

/*termux-clipboard----------------------------------*/

int termux_clipboard_get(char **out)
{
    return cmdsh(out, "termux-clipboard-get");
}

int termux_clipboard_set(const char *str)
{
    if (!str)
    {
        return -1;
    }

    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-clipboard-set");

    CMD_OP_ADD(ks, "", str);

    int ret = cmdout(ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*termux-contact-list--------------------------------*/

int termux_contact_list(char **out)
{
    return cmdsh(out, "termux-contact-list");
}

/*termux-dialog--------------------------------------*/

int termux_dialog_time(char **out, const char *t)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog time");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_text(char **out, const char *t, const char *i, const char *op)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog text");

    if (op)
    {
        (void)ksprintf(ks, " -%s", op);
    }

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (i)
    {
        CMD_OP_ADD(ks, "-i", i);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_speech(char **out, const char *t, const char *i)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog speech");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (i)
    {
        CMD_OP_ADD(ks, "-i", i);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_spinner(char **out, const char *t, const char *v)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog spinner");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (v)
    {
        CMD_OP_ADD(ks, "-v", v);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_sheet(char **out, const char *t, const char *v)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog sheet");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (v)
    {
        CMD_OP_ADD(ks, "-v", v);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_radio(char **out, const char *t, const char *v)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog radio");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (v)
    {
        CMD_OP_ADD(ks, "-v", v);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_date(char **out, const char *t, const char *d)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog date");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (d)
    {
        CMD_OP_ADD(ks, "-d", d);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_counter(char **out, const char *t, const char *r)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog counter");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (r)
    {
        CMD_OP_ADD(ks, "-r", r);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_checkbox(char **out, const char *t, const char *v)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog checkbox");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (v)
    {
        CMD_OP_ADD(ks, "-v", v);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_dialog_confirm(char **out, const char *t, const char *i)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-dialog confirm");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (i)
    {
        CMD_OP_ADD(ks, "-i", i);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*download-------------------------------------------*/

int termux_download(const char *url, const char *t, const char *d)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-download");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (d)
    {
        CMD_OP_ADD(ks, "-d", d);
    }

    int ret = -1;

    if (url)
    {
        CMD_OP_ADD(ks, "", url);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

/*fingerprint-----------------------------------------*/

int termux_fingerprint(char **out, const char *t, const char *d, const char *s, const char *c)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-fingerprint");

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (d)
    {
        CMD_OP_ADD(ks, "-d", d);
    }

    if (s)
    {
        CMD_OP_ADD(ks, "-s", s);
    }

    if (c)
    {
        CMD_OP_ADD(ks, "-c", c);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*termux-infrared-------------------------------------*/

int termux_infrared_frequencies(char **out)
{
    return cmdsh(out, "termux-infrared-frequencies");
}

int termux_infrared_transmit(char **out, int f, int num)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-infrared-transmit -f '%i' '%i'", f, num);

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*localtion-------------------------------------------*/

int termux_location(char **out, const char *p, const char *r)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-location");

    if (p)
    {
        CMD_OP_ADD(ks, "-p", p);
    }

    if (r)
    {
        CMD_OP_ADD(ks, "-r", r);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*media-----------------------------------------------*/

int termux_media_scan(char **out, const char *filename, const char *op)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-media-scan");

    if (op)
    {
        (void)ksprintf(ks, " -%s", op);
    }

    int ret = -1;

    if (filename)
    {
        CMD_OP_ADD(ks, "", filename);

        ret = cmdsh(out, ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

int termux_media_player(char **out, const char *op, const char *filename)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-media-player");

    if (op)
    {
        (void)ksprintf(ks, " %s", op);
    }

    if (filename)
    {
        CMD_OP_ADD(ks, "", filename);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*termux-microphone-record---------------------------------------*/

int termux_microphone_record(char **out, const Termux_record *op_s, const char *op)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-microphone-record");

    if (op)
    {
        (void)ksprintf(ks, " -%s", op);
    }

    if (op_s)
    {
        if (op_s->file)
        {
            CMD_OP_ADD(ks, "-f", op_s->file);
        }

        if (op_s->limit)
        {
            (void)ksprintf(ks, " -l %u", op_s->limit);
        }

        if (op_s->encoder)
        {
            CMD_OP_ADD(ks, "-e", op_s->encoder);
        }

        if (op_s->bitrate)
        {
            (void)ksprintf(ks, " -b %u", op_s->bitrate);
        }

        if (op_s->rate)
        {
            (void)ksprintf(ks, " -r %u", op_s->rate);
        }

        if (op_s->count)
        {
            (void)ksprintf(ks, " -c %u", op_s->count);
        }
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*termux-notification--------------------------------------------*/

int termux_notification(const Termux_noti *op)
{
    int        ret = -1;
    kstring_t *ks  = ks_init();
    (void)ksprintf(ks, "termux-notification");

    if (op)
    {
        if (op->alert_once)
        {
            (void)ksprintf(ks, " --alert-once");
        }
        if (op->ongoing)
        {
            (void)ksprintf(ks, " --ongoing");
        }
        if (op->sound)
        {
            (void)ksprintf(ks, " --sound");
        }
        if (op->media_previous)
        {
            (void)ksprintf(ks, " --media-previous");
        }
        if (op->media_next)
        {
            (void)ksprintf(ks, " --media-next");
        }
        if (op->media_play)
        {
            (void)ksprintf(ks, " --media-play");
        }
        if (op->media_pause)
        {
            (void)ksprintf(ks, " --media-pause");
        }

        if (op->content)
        {
            CMD_OP_ADD(ks, "--content", op->content);
        }

        if (op->action)
        {
            CMD_OP_ADD(ks, "--action", op->action);
        }

        if (op->button1)
        {
            CMD_OP_ADD(ks, "--button1", op->button1);
        }

        if (op->button1_action)
        {
            CMD_OP_ADD(ks, "--button1-action", op->button1_action);
        }

        if (op->button2)
        {
            CMD_OP_ADD(ks, "--button2", op->button2);
        }

        if (op->button2_action)
        {
            CMD_OP_ADD(ks, "--button2-action", op->button2_action);
        }

        if (op->button3)
        {
            CMD_OP_ADD(ks, "--button3", op->button3);
        }

        if (op->button3_action)
        {
            CMD_OP_ADD(ks, "--button3-action", op->button3_action);
        }

        if (op->group)
        {
            CMD_OP_ADD(ks, "--group", op->group);
        }

        if (op->image_path)
        {
            CMD_OP_ADD(ks, "--image-path", op->image_path);
        }

        if (op->led_color)
        {
            CMD_OP_ADD(ks, "--led-color", op->led_color);
        }

        if (op->on_delete)
        {
            CMD_OP_ADD(ks, "--on-delete", op->on_delete);
        }

        if (op->priority)
        {
            CMD_OP_ADD(ks, "--priority", op->priority);
        }

        if (op->title)
        {
            CMD_OP_ADD(ks, "--title", op->title);
        }

        if (op->vibrate)
        {
            CMD_OP_ADD(ks, "--vibrate", op->vibrate);
        }

        if (op->type)
        {
            CMD_OP_ADD(ks, "--type", op->type);
        }

        if (op->id)
        {
            (void)ksprintf(ks, " --id %u", op->id);
        }

        if (op->led_off)
        {
            (void)ksprintf(ks, " --led-off %u", op->led_off);
        }

        if (op->led_on)
        {
            (void)ksprintf(ks, " --led-on %u", op->led_on);
        }
    }

    ret = cmdout(ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_notification_list(char **out)
{
    return cmdsh(out, "termux-notification-list");
}

int termux_notification_remove(int id)
{
    int ret = -1;
    if (id > -1)
    {
        kstring_t *ks = ks_init();
        ksprintf(ks, "termux-notification-remove %i", id);

        ret = cmdout(ks_str(ks));

        PFREE(ks_free, ks);
    }
    return ret;
}

/*termux-open-----------------------------------------------*/

int termux_open(const char *path_url, int select, const char *type)
{
    int        ret = -1;
    kstring_t *ks  = ks_init();
    (void)ksprintf(ks, "termux-open");

    switch (select)
    {
    case 1:
        (void)ksprintf(ks, " --send");
        break;

    case 2:
        (void)ksprintf(ks, " --chooser");
        break;

    default:
        (void)ksprintf(ks, " --view");
        break;
    }

    if (type)
    {
        (void)ksprintf(ks, " --content-type %s", type);
    }

    if (path_url)
    {
        CMD_OP_ADD(ks, "", path_url);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

int termux_open_url(const char *url)
{
    int ret = -1;

    if (url)
    {
        kstring_t *ks = ks_init();

        char *tmp = NULL;
        cmdstr(&tmp, url);
        (void)ksprintf(ks, "termux-open-url \"%s\"", tmp);
        PFREE(free, tmp);

        ret = cmdout(ks_str(ks));

        PFREE(ks_free, ks);
    }

    return ret;
}

/*termux-sensor--------------------------------------------*/

int termux_sensor(char **out, const char *s, int ms, int n, const char *op)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-sensor");
    if (op)
    {
        (void)ksprintf(ks, " -%s", op);
    }

    if (s)
    {
        CMD_OP_ADD(ks, "-s", s);
    }

    if (ms > 0)
    {
        (void)ksprintf(ks, " -d %i", ms);
    }

    if (n > 0)
    {
        (void)ksprintf(ks, " -n %i", n);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*termux-sms--------------------------------------------*/

int termux_sms_list(char **out, const char *t, int l, int o, const char *op)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-sms-list");

    if (op)
    {
        (void)ksprintf(ks, " -%s", op);
    }

    if (t)
    {
        CMD_OP_ADD(ks, "-t", t);
    }

    if (l > 0)
    {
        (void)ksprintf(ks, " -l %i", l);
    }

    if (o > -1)
    {
        (void)ksprintf(ks, " -o %i", o);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

int termux_sms_send(const char *numbers, const char *text)
{
    int        ret = -1;
    kstring_t *ks  = ks_init();
    (void)ksprintf(ks, "termux-sms-send");

    if (numbers)
    {
        CMD_OP_ADD(ks, "-n", numbers);
    }

    if (text)
    {
        CMD_OP_ADD(ks, "", text);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

/*termux-speech-to-text----------------------------------*/

int termux_speech_to_text(char **out)
{
    return cmdsh(out, "termux-speech-to-text");
}

/*termux-storage-get------------------------------------*/

int termux_storage_get(const char *filename)
{
    int        ret = -1;
    kstring_t *ks  = ks_init();

    if (filename)
    {
        char *tmp = NULL;
        cmdstr(&tmp, filename);
        (void)ksprintf(ks, "termux-storage-get \"%s\"", tmp);
        PFREE(free, tmp);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

/*termux-telephony--------------------------------------*/

int termux_telephony_call(const char *num)
{
    int        ret = -1;
    kstring_t *ks  = ks_init();

    if (num)
    {
        char *tmp = NULL;
        cmdstr(&tmp, num);
        (void)ksprintf(ks, "termux-telephony-call \"%s\"", tmp);
        PFREE(free, tmp);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

int termux_telephony_cellinfo(char **out)
{
    return cmdsh(out, "termux-telephony-cellinfo");
}

int termux_telephony_deviceinfo(char **out)
{
    return cmdsh(out, "termux-telephony-deviceinfo");
}

/*torch----------------------------------------------*/

int termux_toast(const char *text, const char *c, const char *b, const char *g, int s)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-toast");

    if (s)
    {
        (void)ksprintf(ks, " -s");
    }

    if (c)
    {
        CMD_OP_ADD(ks, "-c", c);
    }

    if (b)
    {
        CMD_OP_ADD(ks, "-b", b);
    }

    if (g)
    {
        CMD_OP_ADD(ks, "-g", g);
    }

    int ret = -1;

    if (text)
    {
        CMD_OP_ADD(ks, "", text);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

/*torch----------------------------------------------*/

int termux_torch(int on)
{
    int ret = -1;
    if (on)
    {
        ret = cmdout("termux-torch on");
    }
    else
    {
        ret = cmdout("termux-torch off");
    }
    return ret;
}

/*tts-----------------------------------------------*/

int termux_tts_engines(char **out)
{
    return cmdsh(out, "termux-tts-engines");
}

int termux_tts_speak(const Termux_tts *op, const char *text)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-tts-speak");

    if (op)
    {
        if (op->engines)
        {
            CMD_OP_ADD(ks, "-e", op->engines);
        }

        if (op->language)
        {
            CMD_OP_ADD(ks, "-l", op->language);
        }

        if (op->region)
        {
            CMD_OP_ADD(ks, "-n", op->region);
        }

        if (op->variant)
        {
            CMD_OP_ADD(ks, "-v", op->variant);
        }

        if (op->stream)
        {
            CMD_OP_ADD(ks, "-s", op->stream);
        }

        if (op->pitch > 0)
        {
            (void)ksprintf(ks, " -e %g", op->pitch);
        }

        if (op->rate > 0)
        {
            (void)ksprintf(ks, " -r %g", op->rate);
        }
    }

    int ret = -1;

    if (text)
    {
        CMD_OP_ADD(ks, "", text);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

/*usb-----------------------------------------------*/

int termux_usb(char **out, const char *path, const char *e, const char *op)
{
    kstring_t *ks = ks_init();
    (void)ksprintf(ks, "termux-usb");

    if (op)
    {
        (void)ksprintf(ks, " -%s", op);  // l r
    }

    if (e)
    {
        CMD_OP_ADD(ks, "-e", e);
    }

    if (path)
    {
        CMD_OP_ADD(ks, "", path);
    }

    int ret = cmdsh(out, ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*vibrate--------------------------------------------*/

int termux_vibrate(int ms, int mute)
{
    int        ret = -1;
    kstring_t *ks  = ks_init();
    (void)ksprintf(ks, "termux-vibrate");

    if (mute)
    {
        (void)ksprintf(ks, " -f");
    }

    if (ms > 0)
    {
        (void)ksprintf(ks, " -d %i", ms);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

/*volume----------------------------------------------*/

int termux_volume(const char *s, int v)
{
    int        ret = -1;
    kstring_t *ks  = ks_init();
    (void)ksprintf(ks, "termux-volume");

    if (s && v > -1)
    {
        (void)ksprintf(ks, " '%s' %i", s, v);
    }

    ret = cmdout(ks_str(ks));

    PFREE(ks_free, ks);
    return ret;
}

/*wallpaper-------------------------------------------*/

int termux_wallpaper(const char *file_url, int screen)
{
    int        ret = -1;
    kstring_t *ks  = ks_init();
    (void)ksprintf(ks, "termux-wallpaper");

    if (screen)
    {
        (void)ksprintf(ks, " -l");
    }

    if (strstr(file_url, "http"))
    {
        (void)ksprintf(ks, " -u");
    }
    else
    {
        (void)ksprintf(ks, " -f");
    }

    if (file_url)
    {
        CMD_OP_ADD(ks, "", file_url);

        ret = cmdout(ks_str(ks));
    }

    PFREE(ks_free, ks);
    return ret;
}

/*wake------------------------------------------------*/

int termux_wake_lock(int mark)
{
    int ret = -1;
    if (mark)
    {
        ret = cmdout("termux-wake-lock");
    }
    else
    {
        ret = cmdout("termux-wake-unlock");
    }
    return ret;
}

/*wifi------------------------------------------------*/

int termux_wifi_connectioninfo(char **out)
{
    return cmdsh(out, "termux-wifi-connectioninfo");
}

int termux_wifi_enable(int mark)
{
    int ret = -1;
    if (mark)
    {
        ret = cmdout("termux-wifi-enable true");
    }
    else
    {
        ret = cmdout("termux-wifi-enable false");
    }
    return ret;
}

int termux_wifi_scaninfo(char **out)
{
    return cmdsh(out, "termux-wifi-scaninfo");
}

/************************ (C) COPYRIGHT tqfx *******************END OF FILE****/
