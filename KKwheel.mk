##
## Auto Generated makefile by CDK
## Do not modify this file, and any manual changes will be erased!!!   
##
## BuildSet
ProjectName            :=KKwheel
ConfigurationName      :=BuildSet
WorkspacePath          :=C:/Users/linzijun/AppData/Roaming/cdk/default_workspace3/
ProjectPath            :=C:/Users/linzijun/Desktop/git/fan-light-hk/
IntermediateDirectory  :=Obj
OutDir                 :=$(IntermediateDirectory)
User                   :=LinZiJun
Date                   :=28/09/2019
CDKPath                :=D:/C-Sky/C-Sky Development Kit
LinkerName             :=csky-elfabiv2-gcc
LinkerNameoption       :=
SIZE                   :=csky-elfabiv2-size
READELF                :=csky-elfabiv2-readelf
CHECKSUM               :=crc32
SharedObjectLinkerName :=
ObjectSuffix           :=.o
DependSuffix           :=.d
PreprocessSuffix       :=.i
DisassemSuffix         :=.asm
IHexSuffix             :=.ihex
BinSuffix              :=.bin
ExeSuffix              :=.elf
LibSuffix              :=.a
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
ElfInfoSwitch          :=-hlS
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
UnPreprocessorSwitch   :=-U
SourceSwitch           :=-c 
ObjdumpSwitch          :=-S
ObjcopySwitch          :=-O ihex
ObjcopyBinSwitch       :=-O binary
OutputFile             :=lib_F101TKey_WheelSlider_1_16
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="KKwheel.txt"
MakeDirCommand         :=mkdir
LinkOptions            :=-mcpu=ck802  -nostartfiles -Wl,--gc-sections  -T"$(ProjectPath)/ckcpu.ld"
IncludeCPath           :=$(IncludeSwitch)"$(ProjectPath)" $(IncludeSwitch)"$(ProjectPath)//TK_Parameter" $(IncludeSwitch)"$(ProjectPath)/include" 
IncludeAPath           :=$(IncludeSwitch)"$(ProjectPath)" -Wa,$(IncludeSwitch)"$(ProjectPath)" $(IncludeSwitch)"$(ProjectPath)//TK_Parameter" -Wa,$(IncludeSwitch)"$(ProjectPath)//TK_Parameter" $(IncludeSwitch)"$(ProjectPath)include" -Wa,$(IncludeSwitch)"$(ProjectPath)include" 
Libs                   :=$(LibrarySwitch)_F101TKey_WheelSlider_1_16_4KEY_256step_2slider 
ArLibs                 := "lib_F101TKey_WheelSlider_1_16_4KEY_256step_2slider" 
LibPath                :=$(LibraryPathSwitch)"$(ProjectPath)" 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       :=csky-elfabiv2-ar rcu
CXX      :=csky-elfabiv2-g++
CC       :=csky-elfabiv2-gcc
AS       :=csky-elfabiv2-gcc
OBJDUMP  :=csky-elfabiv2-objdump
OBJCOPY  :=csky-elfabiv2-objcopy
CXXFLAGS :=-mcpu=ck802    -O2  -g3  -Wall -mistack 
CFLAGS   :=-mcpu=ck802    -O2  -g3  -Wall -mistack 
ASFLAGS  :=-mcpu=ck802    -Wa,--gdwarf2    


Objects0=$(IntermediateDirectory)/arch_crt0$(ObjectSuffix) $(IntermediateDirectory)/arch_apt32f101_mem_init$(ObjectSuffix) $(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/apt32f101_interrupt$(ObjectSuffix) $(IntermediateDirectory)/apt32f101_initial$(ObjectSuffix) $(IntermediateDirectory)/FWlib_apt32f101_gpio$(ObjectSuffix) $(IntermediateDirectory)/FWlib_apt32f101_syscon$(ObjectSuffix) $(IntermediateDirectory)/FWlib_apt32f101$(ObjectSuffix) $(IntermediateDirectory)/FWlib_apt32f101_ck802$(ObjectSuffix) $(IntermediateDirectory)/FWlib_apt32f101_tkey_Parameter$(ObjectSuffix) \
	$(IntermediateDirectory)/FWlib_apt32f101_WheelSlider_Parameter$(ObjectSuffix) $(IntermediateDirectory)/FWlib_apt32f101_counta$(ObjectSuffix) $(IntermediateDirectory)/FWlib_apt32f101_gtc$(ObjectSuffix) $(IntermediateDirectory)/FWlib_apt32f101_uart$(ObjectSuffix) $(IntermediateDirectory)/__rt_entry$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory)/$(OutputFile)

$(IntermediateDirectory)/$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo linking...
	@$(LinkerName) $(OutputSwitch)"$(IntermediateDirectory)/$(OutputFile)$(ExeSuffix)" $(LinkerNameoption) @$(ObjectsFileList)  $(LibPath) $(Libs)  -Wl,--whole-archive  -Wl,--no-whole-archive $(LinkOptions)
	@echo generating hex file...
	@$(OBJCOPY) $(ObjcopySwitch) "$(ProjectPath)/$(IntermediateDirectory)/$(OutputFile)$(ExeSuffix)"  "$(ProjectPath)/Obj/$(OutputFile)$(IHexSuffix)" 
	@echo size of target:
	@$(SIZE) "$(ProjectPath)$(IntermediateDirectory)/$(OutputFile)$(ExeSuffix)" 
	@echo -n "checksum value of target:  "
	@$(CHECKSUM) "$(ProjectPath)/$(IntermediateDirectory)/$(OutputFile)$(ExeSuffix)" 
	
MakeIntermediateDirs:
	@test -d Obj || $(MakeDirCommand) Obj

	@test -d Lst || $(MakeDirCommand) Lst

$(IntermediateDirectory)/.d:
	@test -d Obj || $(MakeDirCommand) Obj
	@test -d Lst || $(MakeDirCommand) Lst


PreBuild:


##
## Objects
##
$(IntermediateDirectory)/arch_crt0$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/arch/crt0.S  
	@echo assembling crt0.S...
	@$(AS) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/arch/crt0.S" $(ASFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/arch_crt0$(ObjectSuffix) $(IncludeAPath)
	@$(CC) $(CFLAGS) $(IncludeAPath) -MG -MP -MT$(IntermediateDirectory)/arch_crt0$(ObjectSuffix) -MF$(IntermediateDirectory)/arch_crt0$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/arch/crt0.S"

Lst/arch_crt0$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/arch/crt0.S
	@echo generating preprocess file of crt0.S...
	@$(CC) $(CFLAGS)$(IncludeAPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/arch_crt0$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/arch/crt0.S"

$(IntermediateDirectory)/arch_apt32f101_mem_init$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/arch/apt32f101_mem_init.c  
	@echo compiling apt32f101_mem_init.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/arch/apt32f101_mem_init.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/arch_apt32f101_mem_init$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/arch_apt32f101_mem_init$(ObjectSuffix) -MF$(IntermediateDirectory)/arch_apt32f101_mem_init$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/arch/apt32f101_mem_init.c"

Lst/arch_apt32f101_mem_init$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/arch/apt32f101_mem_init.c
	@echo generating preprocess file of apt32f101_mem_init.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/arch_apt32f101_mem_init$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/arch/apt32f101_mem_init.c"

$(IntermediateDirectory)/main$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/main.c  
	@echo compiling main.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/main.c"

Lst/main$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/main.c
	@echo generating preprocess file of main.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/main$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/main.c"

$(IntermediateDirectory)/apt32f101_interrupt$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_interrupt.c  
	@echo compiling apt32f101_interrupt.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_interrupt.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/apt32f101_interrupt$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/apt32f101_interrupt$(ObjectSuffix) -MF$(IntermediateDirectory)/apt32f101_interrupt$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_interrupt.c"

Lst/apt32f101_interrupt$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_interrupt.c
	@echo generating preprocess file of apt32f101_interrupt.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/apt32f101_interrupt$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_interrupt.c"

$(IntermediateDirectory)/apt32f101_initial$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_initial.c  
	@echo compiling apt32f101_initial.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_initial.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/apt32f101_initial$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/apt32f101_initial$(ObjectSuffix) -MF$(IntermediateDirectory)/apt32f101_initial$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_initial.c"

Lst/apt32f101_initial$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_initial.c
	@echo generating preprocess file of apt32f101_initial.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/apt32f101_initial$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/apt32f101_initial.c"

$(IntermediateDirectory)/FWlib_apt32f101_gpio$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gpio.c  
	@echo compiling apt32f101_gpio.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gpio.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101_gpio$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101_gpio$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101_gpio$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gpio.c"

Lst/FWlib_apt32f101_gpio$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gpio.c
	@echo generating preprocess file of apt32f101_gpio.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101_gpio$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gpio.c"

$(IntermediateDirectory)/FWlib_apt32f101_syscon$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_syscon.c  
	@echo compiling apt32f101_syscon.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_syscon.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101_syscon$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101_syscon$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101_syscon$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_syscon.c"

Lst/FWlib_apt32f101_syscon$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_syscon.c
	@echo generating preprocess file of apt32f101_syscon.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101_syscon$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_syscon.c"

$(IntermediateDirectory)/FWlib_apt32f101$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101.c  
	@echo compiling apt32f101.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101.c"

Lst/FWlib_apt32f101$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101.c
	@echo generating preprocess file of apt32f101.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101.c"

$(IntermediateDirectory)/FWlib_apt32f101_ck802$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_ck802.c  
	@echo compiling apt32f101_ck802.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_ck802.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101_ck802$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101_ck802$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101_ck802$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_ck802.c"

Lst/FWlib_apt32f101_ck802$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_ck802.c
	@echo generating preprocess file of apt32f101_ck802.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101_ck802$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_ck802.c"

$(IntermediateDirectory)/FWlib_apt32f101_tkey_Parameter$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_tkey_Parameter.c  
	@echo compiling apt32f101_tkey_Parameter.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_tkey_Parameter.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101_tkey_Parameter$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101_tkey_Parameter$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101_tkey_Parameter$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_tkey_Parameter.c"

Lst/FWlib_apt32f101_tkey_Parameter$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_tkey_Parameter.c
	@echo generating preprocess file of apt32f101_tkey_Parameter.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101_tkey_Parameter$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_tkey_Parameter.c"

$(IntermediateDirectory)/FWlib_apt32f101_WheelSlider_Parameter$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_WheelSlider_Parameter.c  
	@echo compiling apt32f101_WheelSlider_Parameter.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_WheelSlider_Parameter.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101_WheelSlider_Parameter$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101_WheelSlider_Parameter$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101_WheelSlider_Parameter$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_WheelSlider_Parameter.c"

Lst/FWlib_apt32f101_WheelSlider_Parameter$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_WheelSlider_Parameter.c
	@echo generating preprocess file of apt32f101_WheelSlider_Parameter.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101_WheelSlider_Parameter$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_WheelSlider_Parameter.c"

$(IntermediateDirectory)/FWlib_apt32f101_counta$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_counta.c  
	@echo compiling apt32f101_counta.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_counta.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101_counta$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101_counta$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101_counta$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_counta.c"

Lst/FWlib_apt32f101_counta$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_counta.c
	@echo generating preprocess file of apt32f101_counta.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101_counta$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_counta.c"

$(IntermediateDirectory)/FWlib_apt32f101_gtc$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gtc.c  
	@echo compiling apt32f101_gtc.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gtc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101_gtc$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101_gtc$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101_gtc$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gtc.c"

Lst/FWlib_apt32f101_gtc$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gtc.c
	@echo generating preprocess file of apt32f101_gtc.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101_gtc$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_gtc.c"

$(IntermediateDirectory)/FWlib_apt32f101_uart$(ObjectSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_uart.c  
	@echo compiling apt32f101_uart.c...
	@$(CC) $(SourceSwitch) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_uart.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FWlib_apt32f101_uart$(ObjectSuffix) $(IncludeCPath)
	@$(CC) $(CFLAGS) $(IncludeCPath) -MG -MP -MT$(IntermediateDirectory)/FWlib_apt32f101_uart$(ObjectSuffix) -MF$(IntermediateDirectory)/FWlib_apt32f101_uart$(DependSuffix) -MM "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_uart.c"

Lst/FWlib_apt32f101_uart$(PreprocessSuffix): C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_uart.c
	@echo generating preprocess file of apt32f101_uart.c...
	@$(CC) $(CFLAGS)$(IncludeCPath) $(PreprocessOnlySwitch) $(OutputSwitch) Lst/FWlib_apt32f101_uart$(PreprocessSuffix) "C:/Users/linzijun/Desktop/git/fan-light-hk/FWlib/apt32f101_uart.c"


$(IntermediateDirectory)/__rt_entry$(ObjectSuffix): $(IntermediateDirectory)/__rt_entry$(DependSuffix)
	@$(AS) $(SourceSwitch) "$(ProjectPath)/$(IntermediateDirectory)/__rt_entry.S" $(ASFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/__rt_entry$(ObjectSuffix) $(IncludeAPath)
	@rm -f $(IntermediateDirectory)/__rt_entry.S
$(IntermediateDirectory)/__rt_entry$(DependSuffix):
	@$(CC) $(CFLAGS) $(IncludeAPath) -MG -MP -MT$(IntermediateDirectory)/__rt_entry$(ObjectSuffix) -MF$(IntermediateDirectory)/__rt_entry$(DependSuffix) -MM "$(ProjectPath)/$(IntermediateDirectory)/__rt_entry.S"

-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	@echo Cleaning target...
	@rm -rf $(IntermediateDirectory)/ $(ObjectsFileList) KKwheel.mk Lst/

clean_internal:
	@rm -rf $(IntermediateDirectory)/*.o $(IntermediateDirectory)/.d $(IntermediateDirectory)/*.d $(IntermediateDirectory)/*.a $(IntermediateDirectory)/*.elf $(IntermediateDirectory)/*.ihex Lst/

