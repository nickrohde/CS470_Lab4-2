##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Lab4
ConfigurationName      :=Debug
WorkspacePath          :=/home/nick/Projects/CS470/Lab4/Lab4
ProjectPath            :=/home/nick/Projects/CS470/Lab4/CS470_Lab4/Lab4
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=nick
Date                   :=21/02/18
CodeLitePath           :=/home/nick/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Lab4.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/client.cpp$(ObjectSuffix) $(IntermediateDirectory)/driver.cpp$(ObjectSuffix) $(IntermediateDirectory)/server.cpp$(ObjectSuffix) $(IntermediateDirectory)/IniParser.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/client.cpp$(ObjectSuffix): client.cpp $(IntermediateDirectory)/client.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/nick/Projects/CS470/Lab4/CS470_Lab4/Lab4/client.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/client.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/client.cpp$(DependSuffix): client.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/client.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/client.cpp$(DependSuffix) -MM client.cpp

$(IntermediateDirectory)/client.cpp$(PreprocessSuffix): client.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/client.cpp$(PreprocessSuffix) client.cpp

$(IntermediateDirectory)/driver.cpp$(ObjectSuffix): driver.cpp $(IntermediateDirectory)/driver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/nick/Projects/CS470/Lab4/CS470_Lab4/Lab4/driver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/driver.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/driver.cpp$(DependSuffix): driver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/driver.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/driver.cpp$(DependSuffix) -MM driver.cpp

$(IntermediateDirectory)/driver.cpp$(PreprocessSuffix): driver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/driver.cpp$(PreprocessSuffix) driver.cpp

$(IntermediateDirectory)/server.cpp$(ObjectSuffix): server.cpp $(IntermediateDirectory)/server.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/nick/Projects/CS470/Lab4/CS470_Lab4/Lab4/server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server.cpp$(DependSuffix): server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/server.cpp$(DependSuffix) -MM server.cpp

$(IntermediateDirectory)/server.cpp$(PreprocessSuffix): server.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server.cpp$(PreprocessSuffix) server.cpp

$(IntermediateDirectory)/IniParser.cpp$(ObjectSuffix): IniParser.cpp $(IntermediateDirectory)/IniParser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/nick/Projects/CS470/Lab4/CS470_Lab4/Lab4/IniParser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IniParser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IniParser.cpp$(DependSuffix): IniParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IniParser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IniParser.cpp$(DependSuffix) -MM IniParser.cpp

$(IntermediateDirectory)/IniParser.cpp$(PreprocessSuffix): IniParser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IniParser.cpp$(PreprocessSuffix) IniParser.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


