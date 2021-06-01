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

.PHONY: $(BUILD) format clean

$(BUILD):
	@cmake -S . -B $@ $(CMAKE_G) -DCMAKE_BUILD_TYPE="Release" && cd $@ && make -j

clean:
	@-git clean -f -d -X

format: fpcode fp app app-termux termux-api main.c main.h main-termux.c
	@-find $^ -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;

