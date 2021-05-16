BUILD = build

ifdef MINGW
CMAKE_G = -G "MinGW Makefiles"
endif
ifdef MSYS
CMAKE_G = -G "MSYS Makefiles"
endif
ifndef CMAKE_G
CMAKE_G = -G "Unix Makefiles"
endif

all:$(BUILD)
	@cd $(BUILD) && cmake .. $(CMAKE_G) -DCMAKE_BUILD_TYPE="Release" && $(MAKE) -j

$(BUILD):
	@-mkdir $@

.PHONY: format clean
format: fpcode fp app app_termux tapi
	@-find $^ -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;
clean:
	@-git clean -f -d -X
