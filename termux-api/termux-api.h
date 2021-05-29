/*!
 @file           termux-api.h
 @brief          api of termux
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-29
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 \n \n
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 \n \n
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* Define to prevent recursive inclusion */
#ifndef __TERMUX_API_H__
#define __TERMUX_API_H__

#undef __BEGIN_DECLS
#undef __END_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

#undef PFREE
#define PFREE(_FUN_, _) \
    do                  \
    {                   \
        (void)_FUN_(_); \
        _ = NULL;       \
    } while (0)

/*!
 @struct         Termux_record
 @brief          termux record optoins
*/
typedef struct
{
    char *       file;     //!< 开始记录到特定文件
    char *       encoder;  //!< 使用指定的编码器(aac, amr_wb, amr_nb)开始记录
    unsigned int limit;    //!< 开始记录指定的限制(以秒为单位, 0不受限制)
    unsigned int bitrate;  //!< 开始记录指定的比特率(以kbps为单位)
    unsigned int rate;     //!< 开始记录指定的采样率(以Hz为单位)
    unsigned int count;    //!< 开始记录指定的通道数(1,2,...)
} Termux_record;

/*!
 @struct         Termux_noti
 @brief          termux notification optoins
*/
typedef struct
{
    int alert_once     : 1;  //!< 在编辑通知时不会发出警报
    int ongoing        : 1;  //!< 固定通知
    int sound          : 1;  //!< 在通知中播放声音
    int media_next     : 1;  //!< 在媒体下一个按钮上执行的操作
    int media_pause    : 1;  //!< 在媒体暂停按钮上执行的操作
    int media_play     : 1;  //!< 在媒体播放按钮上执行的操作
    int media_previous : 1;  //!< 在媒体上一个按钮上执行的操作

    char *       content;         //!< 内容显示在通知中.将优先于stdin.
    char *       action;          //!< 按下通知时要执行的动作
    char *       button1;         //!< 在第一个通知按钮上显示的文字
    char *       button1_action;  //!< 在第一个通知按钮上执行的操作
    char *       button2;         //!< 在第二个通知按钮上显示的文字
    char *       button2_action;  //!< 在第二个通知按钮上执行的操作
    char *       button3;         //!< 在第三个通知按钮上显示的文字
    char *       button3_action;  //!< 在第三个通知按钮上执行的操作
    char *       group;           //!< 通知组(与同一组的通知一起显示)
    unsigned int id;              //!< 通知ID(将覆盖以前所有具有相同ID的通知)
    char *       image_path;      //!< 通知中将显示的图像的绝对路径
    char *       led_color;       //!< 指示灯的闪烁颜色为RRGGBB(默认值: 无)
    unsigned int led_off;         //!< 闪烁时LED熄灭的毫秒数(默认值: 800)
    unsigned int led_on;          //!< 指示灯闪烁的毫秒数(默认值: 800)
    char *       on_delete;       //!< 清除通知时执行的操作
    char *       priority;        //!< 通知优先级(high/low/max/min/default)
    char *       title;           //!< 显示的通知标题
    char *       vibrate;         //!< 振动模式, 逗号分隔为500,1000,200
    char *       type;            //!< 使用的通知样式(default/media)
} Termux_noti;

/*!
 @struct         Termux_tts
 @brief          termux tts optoins
*/
typedef struct
{
    char *engines;   //!< 要使用的TTS引擎(请参阅termux-tts-engines)
    char *language;  //!< 要使用的语言(引擎可能不支持)
    char *region;    //!< 要说的语言区域
    char *variant;   //!< 所用语言的变体
    char *stream;    //!< 要使用的音频流(默认值: NOTIFICATION), 其中一种:
                     //!< ALARM, MUSIC, NOTIFICATION, RING, SYSTEM, VOICE_CALL
    double pitch;    //!< 用于演讲的音调.
                     //!< 1.0是正常音高较低的值会降低合成语音的音调,更大的值会增加它.
    double rate;     //!< 使用的语速. 正常语速是1.0
                     //!< 较低的值会使语音变慢(0.5是正常语速的一半)
                     //!< 而更大的价值会加速它(2.0是正常语速的两倍).
} Termux_tts;

__BEGIN_DECLS

/*!
 @brief          获取有关音频功能的信息.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      "PROPERTY_OUTPUT_SAMPLE_RATE": "48000",
      "PROPERTY_OUTPUT_FRAMES_PER_BUFFER": "192",
      "AUDIOTRACK_SAMPLE_RATE": 48000,
      "AUDIOTRACK_BUFFER_SIZE_IN_FRAMES": 3844,
      "AUDIOTRACK_SAMPLE_RATE_LOW_LATENCY": 48000,
      "AUDIOTRACK_BUFFER_SIZE_IN_FRAMES_LOW_LATENCY": 384,
      "BLUETOOTH_A2DP_IS_ON": false,
      "WIREDHEADSET_IS_CONNECTED": false
  }
*/
extern int termux_audio_info(char **out);

/*!
 @brief          获取设备电池的状态.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      "health": "GOOD",
      "percentage": 87,
      "plugged": "PLUGGED_AC",
      "status": "CHARGING",
      "temperature": 35.0,
      "current": -110000
  }
*/
extern int termux_battery_status(char **out);

/*!
 @brief          将屏幕亮度设置为0至255或auto
 @param[in]      num: -1(auto) 0-255
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_brightness(int num);

/*!
 @brief          列出通话记录历史记录
 @param[out]     out: the pointer of buffer variable
 @param[in]      l: 通话记录列表中的限制偏移量(默认值: 10)
 @param[in]      o: 在呼叫日志列表中的偏移量(默认值: 0)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
 [
  {
   "name": "中国移动",
   "phone_number": "02310086",
   "type": "OUTGOING",
   "date": "2021-01-01 22:17:48",
   "duration": "00:00"
  },
 ]
*/
extern int termux_call_log(char **out,
                           int    l,
                           int    o);

/*!
 @brief          获取有关设备相机的信息.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
 [
  {
      'id': '0',
      'facing': 'back',
      'jpeg_output_sizes': [
          {'width': 4160, 'height': 3120},
          {'width': 4160, 'height': 2336},
          {'width': 3104, 'height': 3104},
          {'width': 3264, 'height': 2448},
          {'width': 3264, 'height': 1840},
          {'width': 1920, 'height': 1080},
          {'width': 1600, 'height': 1200},
          {'width': 1200, 'height': 1200},
          {'width': 1440, 'height': 1080},
          {'width': 1280, 'height': 960},
          {'width': 1280, 'height': 768},
          {'width': 1280, 'height': 720},
          {'width': 1024, 'height': 768},
          {'width': 960, 'height': 720},
          {'width': 800, 'height': 600},
          {'width': 864, 'height': 480},
          {'width': 800, 'height': 480},
          {'width': 720, 'height': 720},
          {'width': 720, 'height': 480},
          {'width': 640, 'height': 480},
          {'width': 640, 'height': 360},
          {'width': 480, 'height': 640},
          {'width': 480, 'height': 360},
          {'width': 480, 'height': 320},
          {'width': 352, 'height': 288},
          {'width': 320, 'height': 240},
          {'width': 240, 'height': 320},
          {'width': 176, 'height': 144}
      ],
      'focal_lengths': [3.5399999618530273],
      'auto_exposure_modes': [
          'CONTROL_AE_MODE_OFF',
          'CONTROL_AE_MODE_ON',
          'CONTROL_AE_MODE_ON_AUTO_FLASH',
          'CONTROL_AE_MODE_ON_ALWAYS_FLASH'
      ],
      'physical_size': {
          'width': 4.748799800872803,
          'height': 3.530240058898926
      },
      'capabilities': [
          'backward_compatible',
          'manual_post_processing',
           6, 4, 7, 9, 'raw'
      ]
  },
 ]
*/
extern int termux_camera_info(char **out);

/*!
 @brief          拍摄照片并将其保存为JPEG格式的文件.
 @param[in]      c: 要使用的摄像机的ID(请参阅termux_camera_info),默认值: 0
 @param[in]      filename: 文件名
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_camera_photo(const char * filename,
                               unsigned int c);

/*!
 @brief          获取系统剪贴板文本
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_clipboard_get(char **out);

/*!
 @brief          设置系统剪贴板文本.
                 要设置的文本要么作为参数提供,
                 要么在未提供参数的情况下从stdin读取.
 @param[in]      str 字符串
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_clipboard_set(const char *str);

/*!
 @brief          列出所有联系人
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval         [{"name":"","number":""}]
*/
extern int termux_contact_list(char **out);

/*!
 @brief          选择一个时间值
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      'code': -1,
      'text': '00:00'
  }
*/
extern int termux_dialog_time(char **     out,
                              const char *t);

/*!
 @brief          输入文本(如果未指定小部件,则为默认值)
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      i: 文本提示(可选)
 @param[in]      op
                 m 多行而不是单行(可选)
                 n 输入数字输入(可选)
                 p 输入密码作为输入(可选)
 @note           不能将[m]与[n]一起使用
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      'code': -1,
      'text': 'text'
  }
*/
extern int termux_dialog_text(char **     out,
                              const char *t,
                              const char *i,
                              const char *op);

/*!
 @brief          使用设备麦克风获取语音
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      i: 文本提示(可选)
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_dialog_speech(char **     out,
                                const char *t,
                                const char *i);

/*!
 @brief          从下拉菜单中选择一个值
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      v: 要使用的逗号delim值(必需)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
 {
      'code': -1,
      'text': '值1',
      'index': 0
  }
*/
extern int termux_dialog_spinner(char **     out,
                                 const char *t,
                                 const char *v);

/*!
 @brief          从滑动底部表中选择一个值
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      v: 要使用的逗号delim值(必需)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      'code': 0,
      'text': '值1',
       'index': 0
  }
*/
extern int termux_dialog_sheet(char **     out,
                               const char *t,
                               const char *v);

/*!
 @brief          从单选按钮中选择一个值
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      v: 要使用的逗号delim值(必需)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      'code': -1,
      'text': '值1',
      'index': 0
  }
*/
extern int termux_dialog_radio(char **     out,
                               const char *t,
                               const char *v);

/*!
 @brief          选择一个日期
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      d: 用于日期小部件输出的SimpleDateFormat模式(可选) 'yyyyMMdd k:m:s'
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      'code': -1,
      'text': '20200901 24:0;0',
      'index': 1
   }
*/
extern int termux_dialog_date(char **     out,
                              const char *t,
                              const char *d);

/*!
 @brief          选择指定范围内的数字
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      r: [min,max,start] 要使用的(3)个数字的逗号delim(可选)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      'code': -1,
      'text': '6',
      'index': 1
  }
*/
extern int termux_dialog_counter(char **     out,
                                 const char *t,
                                 const char *r);

/*!
 @brief          使用复选框选择多个值
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      v: 要使用的逗号delim值(必需)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      'code': -1,
      'text': '[值1, 值2]',
      'index': 1,
      'values': [
          {'index': 0, 'text': '值1'},
          {'index': 1, 'text': '值2'}
      ]
  }
*/
extern int termux_dialog_checkbox(char **     out,
                                  const char *t,
                                  const char *v);

/*!
 @brief          显示确认对话框
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 设置对话框的标题(可选)
 @param[in]      i: 文本提示(可选)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      'code': 0,
      'text': 'yes'('no'),
      'index': 1
  }
*/
extern int termux_dialog_confirm(char **     out,
                                 const char *t,
                                 const char *i);

/*!
 @brief          使用系统下载管理器下载资源.
                 /data/data/com.android.providers.downloads/cache/
 @param[in]      url: 下载链接
 @param[in]      d: 下载请求通知的描述
 @param[in]      t: 下载请求通知的标题
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_download(const char *url,
                           const char *t,
                           const char *d);

/*!
 @brief          使用设备上的指纹传感器检查身份验证
 @warning        仅在Nougat和更高版本上可用
 @param[out]     out: the pointer of buffer variable
 @param[in]      t: 标题
 @param[in]      d: 描述
 @param[in]      s: 字幕
 @param[in]      c: 取消
 @retval
  {
      'errors': [],
      'failed_attempts': 0,
      'auth_result': 'AUTH_RESULT_SUCCESS'
  }
  {
      'errors': [],
      'failed_attempts': 0,
      'auth_result': 'AUTH_RESULT_FAILURE'
  }
*/
extern int termux_fingerprint(char **     out,
                              const char *t,
                              const char *d,
                              const char *s,
                              const char *c);

/*!
 @brief          查询红外发射器支持的载波频率.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval         [{"min":30000,"max":30000},]
*/
extern int termux_infrared_frequencies(char **out);

/*!
 @brief          发射红外线图案. 该模式以逗号分隔的开/关间隔指定,
                 例如 "20,50,20,30" . 仅传输短于2秒的码型.
 @param[out]     out: the pointer of buffer variable
 @param[in]      f: IR载波频率, 以赫兹为单位
 @param[in]      num
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_infrared_transmit(char **out,
                                    int    f,
                                    int    num);

/*!
 @brief          获取设备位置.
 @param[out]     out: the pointer of buffer variable
 @param[in]      p: 程序位置提供程序 [gps/network/passive] (默认值: gps)
 @param[in]      r: 请求一次 [once/last/updates] 的请求(默认值: once)
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      "latitude": 100.455187,
      "longitude": 100.529537,
      "altitude": 0.0,
      "accuracy": 100.0,
      "bearing": 0.0,
      "speed": 0.0,
      "elapsedMs": 4,
      "provider": "network"
  }
*/
extern int termux_location(char **     out,
                           const char *p,
                           const char *r);

/*!
 @brief          扫描指定的文件, 并将其添加到媒体内容提供程序.
 @param[out]     out: the pointer of buffer variable
 @param[in]      filename: 要扫描的文件名
 @param[in]      op: r递归扫描目录 v详细模式
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_media_scan(char **     out,
                             const char *filename,
                             const char *op);

/*!
 @brief          播放器
 @param[out]     out: the pointer of buffer variable
 @param[in]      op:
                 play 如果暂停则继续播放
                 info 显示当前播放信息
                 pause 暂停播放
                 stop 退出播放
 @param[in]      filename: 播放文件名
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_media_player(char **     out,
                               const char *op,
                               const char *filename);

/*!
 @brief          使用设备上的麦克风录制
 @param[out]     out: the pointer of buffer variable
 @param[in]      op
                 d 使用默认设置开始录制
                 i 获取有关当前录制的信息
                 q 退出录音
 @param[in]      struct_op: struct Termux_record
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_microphone_record(char **              out,
                                    const Termux_record *struct_op,
                                    const char *         op);

/*!
 @brief          显示系统通知. 内容文本使用 -c/--content 指定或从stdin中读取.
 @param[in]      op: struct Termux_noti
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_notification(const Termux_noti *op);

/*!
 @brief          显示当前显示的通知列表.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  [
      {
          "id": 1337,
          "tag": "",
          "key": "0|com.termux|1337|null|10141",
          "group": "",
          "packageName": "com.termux",
          "title": "Termux",
          "content": "1 session",
          "when": 1599015058125
      }
  ]
*/
extern int termux_notification_list(char **out);

/*!
 @brief          删除先前用termux-notification --id显示的通知.
 @param[in]      id
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_notification_remove(int id);

/*!
 @brief          在外部应用程序中打开文件或URL
 @param[in]      path_url: 路径或者链接
 @param[in]      select:
                 0 应共享文件进行查看（默认）
                 1 文件应该共享以发送
                 2 应始终显示应用选择器
 @param[in]      type: 指定要使用的内容类型
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_open(const char *path_url,
                       int         select,
                       const char *type);

/*!
 @brief          打开一个URL进行查看
 @param[in]      url: 链接
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_open_url(const char *url);

/*!
 @brief          获取有关传感器类型以及实时数据的信息
 @param[out]     out: the pointer of buffer variable
 @param[in]      op:
                 a 全部收听所有传感器(警告! 可能会对电池产生影响)
                 c 清除执行清除(释放传感器资源)
                 l 列表显示可用传感器的列表
 @param[in]      s: 要监听的传感器(可以只包含部分名称)
 @param[in]      ms 接收新传感器更新之前的延迟时间(以毫秒为单位)
 @param[in]      n: 读取传感器的次数(默认值:连续)(分钟:1
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_sensor(char **     out,
                         const char *s,
                         int         ms,
                         int         n,
                         const char *op);

/*!
 @brief          列出短信
 @param[out]     out: the pointer of buffer variable
 @param[in]      op: d 显示创建消息的日期 n 显示电话号码
 @param[in]      l: 短信列表中的限制偏移量(默认值: 10)
 @param[in]      o: 短信列表中的偏移量(默认值: 0)
 @param[in]      t: 要列出的消息类型(默认值: inbox): all|inbox|sent|draft|outbox
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_sms_list(char **     out,
                           const char *t,
                           int         l,
                           int         o,
                           const char *op);

/*!
 @brief          将SMS消息发送到指定的收件人号码.
                 要发送的文本要么作为参数提供,
                 要么在未提供参数的情况下从stdin读取.
 @param[in]      number: 收件人号码-用逗号分隔多个号码
 @param[in]      text: 文本
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_sms_send(const char *numbers,
                           const char *text);

/*!
 @brief          将语音转换为文本, 将部分匹配项发送到stdout.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_speech_to_text(char **out);

/*!
 @brief          向系统请求文件并将其输出到指定文件.
 @param[in]      filename: 文件名
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_storage_get(const char *filename);

/*!
 @brief          拨打电话号码
 @param[in]      num: 电话号码
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_telephony_call(const char *num);

/*!
 @brief          从设备上的所有无线电(包括主要和相邻小区)获取有关所有观察到的小区信息的信息.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_telephony_cellinfo(char **out);

/*!
 @brief          获取有关电话设备的信息.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  {
      "data_activity": "none",
      "data_state": "disconnected",
      "device_id": "867441037469887",
      "device_software_version": "04",
      "phone_count": 2,
      "phone_type": "gsm",
      "network_operator": "46000",
      "network_operator_name": "中国移动",
      "network_country_iso": "cn",
      "network_type": "lte",
      "network_roaming": false,
      "sim_country_iso": "cn",
      "sim_operator": "46001",
      "sim_operator_name": "CMCC",
      "sim_serial_number": "8986003231AA73832693",
      "sim_subscriber_id": "460021238352693",
      "sim_state": "ready"
  }
*/
extern int termux_telephony_deviceinfo(char **out);

/*!
 @brief          在Toast中显示文本(瞬态弹出窗口).
                 要显示的文本作为参数提供, 或者如果未提供参数, 则从stdin读取.
 @note           颜色可以是标准名称(即red)或6/8位十六进制值(即"#FF0000"或"#FFFF0000"),
                 其顺序为(AA)RRGGBB. 无效的颜色将恢复为默认值.
 @param[in]      text: 显示的文本
 @param[in]      c: 设置文本颜色(default: white)
 @param[in]      b: 设置背景颜色(default: gray)
 @param[in]      g: 设置烤面包的位置 [top, middle, or bottom] (default: middle)
 @param[in]      s: 1 只显示片刻
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_toast(const char *text,
                        const char *c,
                        const char *b,
                        const char *g,
                        int         s);

/*!
 @brief          在设备上切换LED手电筒
 @param[in]      on: 1 0
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_torch(int on);

/*!
 @brief          获取有关可用的文本语音转换(TTS)引擎的信息.
                 可以使用-e选项将引擎的名称提供给termux-tts-speak命令.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
 [
      {
          "name": "com.iflytek.speechsuite",
          "label": "讯飞语音引擎",
          "default": true
      },
      {
          "name": "com.svox.pico",
          "label": "Pico TTS",
           "default": false
       }
  ]
*/
extern int termux_tts_engines(char **out);

/*!
 @brief          使用系统文本语音转换(TTS)引擎说出文本.
                 要说的文本作为参数提供,
                 或者如果未提供参数, 则从stdin读取.
 @param[in]      text: 文本
 @param[in]      op: struct Termux_tts
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_tts_speak(const Termux_tts *op,
                            const char *      text);

/*!
 @brief          列出或访问USB设备. 无法直接访问设备, 仅使用termux-usb.
 @param[out]     out: the pointer of buffer variable
 @param[in]      path: 路径
 @param[in]      op: l 列出可用的设备   r 显示许可权请求对话框(如有必要)
 @param[in]      e: 命令执行带有文件描述符的指定命令引用设备作为其参数
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_usb(char **     out,
                      const char *path,
                      const char *e,
                      const char *op);

/*!
 @brief          振动设备.
 @param[in]      ms: 持续时间以毫秒为单位的振动持续时间(默认值: 1000)
 @param[in]      mute: 1 即使在静音模式下也能振动
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_vibrate(int ms,
                          int mute);

/*!
 @brief          更改音频流的音量.
 @param[in]      s: alarm, music, notification, ring, system, call
 @param[in]      v: 音量大小
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  [
      {
          "stream": "call",
          "volume": 5,
          "max_volume": 5
      },
      {
          "stream": "system",
          "volume": 3,
          "max_volume": 7
      },
      {
          "stream": "ring",
          "volume": 3,
          "max_volume": 7
      },
      {
          "stream": "music",
          "volume": 7,
          "max_volume": 15
      },
      {
          "stream": "alarm",
          "volume": 7,
          "max_volume": 7
      },
      {
          "stream": "notification",
          "volume": 3,
          "max_volume": 7
      }
  ]
*/
extern int termux_volume(const char *s,
                         int         v);

/*!
 @brief          更改设备上的墙纸
 @param[in]      file_url: 从文件设置墙纸或从url资源设置墙纸
 @param[in]      screen: 1 设置用于锁屏的墙纸(Nougat及更高版本)
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_wallpaper(const char *file_url,
                            int         screen);

/*!
 @brief          获取Termux唤醒锁,  以防止CPU休眠.
 @param[in]      mark: 1(lock) 0(unlock)
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_wake_lock(int mark);

/*!
 @brief          开启/关闭Wi-Fi
 @param[in]      mark: 1(on) 0(off)
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_wifi_enable(int mark);

/*!
 @brief          获取有关上一次wifi扫描的信息.
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
 @retval
  [
      {
          "bssid": "4c:bc:98:04:5a:94",
          "frequency_mhz": 2452,
          "rssi": -41,
          "ssid": "",
          "timestamp": 31569432017,
          "channel_bandwidth_mhz": "40",
          "center_frequency_mhz": 2442
      }
  ]
*/
extern int termux_wifi_scaninfo(char **out);

/*!
 @brief          获取有关当前wifi连接的信息
 @param[out]     out: the pointer of buffer variable
 @return         The status
  @retval        0  success
  @retval        -1 failure
*/
extern int termux_wifi_connectioninfo(char **out);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __TERMUX_API_H__ */

/* END OF FILE */
