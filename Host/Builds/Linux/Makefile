# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DJUCER_LINUX_MAKE_7346DA2A=1 -DJUCE_APP_VERSION=0.5 -DJUCE_APP_VERSION_HEX=0x500 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama) -pthread -I../../JuceLibraryCode -I../../JuceLibraryCode/modules $(CPPFLAGS)
  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -I ~/SDKs -std=gnu++11 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -L/usr/X11R6/lib/ $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama) -lGL -ldl -lpthread -lrt  $(LDFLAGS)

  TARGET := pfm2Editor
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DJUCER_LINUX_MAKE_7346DA2A=1 -DJUCE_APP_VERSION=0.5 -DJUCE_APP_VERSION_HEX=0x500 $(shell pkg-config --cflags alsa freetype2 libcurl x11 xext xinerama) -pthread -I../../JuceLibraryCode -I../../JuceLibraryCode/modules $(CPPFLAGS)
  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -Os -I ~/SDKs -std=gnu++11 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ $(shell pkg-config --libs alsa freetype2 libcurl x11 xext xinerama) -lGL -ldl -lpthread -lrt  $(LDFLAGS)

  TARGET := pfm2Editor
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS := \
  $(JUCE_OBJDIR)/AlgoPNG_cf66d571.o \
  $(JUCE_OBJDIR)/Enveloppe_978f1a6b.o \
  $(JUCE_OBJDIR)/EnveloppeAbstract_ac9367ad.o \
  $(JUCE_OBJDIR)/EnveloppeFree1_8522c964.o \
  $(JUCE_OBJDIR)/EnveloppeFree2_8530e0e5.o \
  $(JUCE_OBJDIR)/MainTabs_1a903dc0.o \
  $(JUCE_OBJDIR)/PanelArpAndFilter_5cf5ba35.o \
  $(JUCE_OBJDIR)/PanelEngine_3d916ae7.o \
  $(JUCE_OBJDIR)/PanelModulation_3a30d121.o \
  $(JUCE_OBJDIR)/PluginEditor_5326167c.o \
  $(JUCE_OBJDIR)/PluginProcessor_e32f2d.o \
  $(JUCE_OBJDIR)/PreenLookAndFeel_f74a21bb.o \
  $(JUCE_OBJDIR)/StepSequencer_c4513266.o \
  $(JUCE_OBJDIR)/exoFont_8e57ed9e.o \
  $(JUCE_OBJDIR)/tinythread_3b828360.o \
  $(JUCE_OBJDIR)/AudioProcessorPlayerWithMidiOutput_efdf50ae.o \
  $(JUCE_OBJDIR)/Main_90ebc5c2.o \
  $(JUCE_OBJDIR)/juce_audio_basics_6b797ca1.o \
  $(JUCE_OBJDIR)/juce_audio_devices_a742c38b.o \
  $(JUCE_OBJDIR)/juce_audio_formats_5a29c68a.o \
  $(JUCE_OBJDIR)/juce_audio_processors_dea3173d.o \
  $(JUCE_OBJDIR)/juce_audio_utils_c7eb679f.o \
  $(JUCE_OBJDIR)/juce_core_75b14332.o \
  $(JUCE_OBJDIR)/juce_cryptography_6de2ebff.o \
  $(JUCE_OBJDIR)/juce_data_structures_72d3da2c.o \
  $(JUCE_OBJDIR)/juce_events_d2be882c.o \
  $(JUCE_OBJDIR)/juce_graphics_9c18891e.o \
  $(JUCE_OBJDIR)/juce_gui_basics_8a6da59c.o \
  $(JUCE_OBJDIR)/juce_gui_extra_4a026f23.o \
  $(JUCE_OBJDIR)/juce_opengl_cd70b4c2.o \

.PHONY: clean

$(JUCE_OUTDIR)/$(TARGET): check-pkg-config $(OBJECTS) $(RESOURCES)
	@echo Linking pfm2Editor
	-@mkdir -p $(JUCE_BINDIR)
	-@mkdir -p $(JUCE_LIBDIR)
	-@mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(BLDCMD)

check-pkg-config:
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors alsa freetype2 libcurl x11 xext xinerama

clean:
	@echo Cleaning pfm2Editor
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping pfm2Editor
	-@$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

$(JUCE_OBJDIR)/AlgoPNG_cf66d571.o: ../../../Plugin/Source/UI/png/AlgoPNG.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AlgoPNG.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Enveloppe_978f1a6b.o: ../../../Plugin/Source/UI/Enveloppe.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Enveloppe.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/EnveloppeAbstract_ac9367ad.o: ../../../Plugin/Source/UI/EnveloppeAbstract.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling EnveloppeAbstract.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/EnveloppeFree1_8522c964.o: ../../../Plugin/Source/UI/EnveloppeFree1.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling EnveloppeFree1.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/EnveloppeFree2_8530e0e5.o: ../../../Plugin/Source/UI/EnveloppeFree2.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling EnveloppeFree2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MainTabs_1a903dc0.o: ../../../Plugin/Source/UI/MainTabs.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MainTabs.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PanelArpAndFilter_5cf5ba35.o: ../../../Plugin/Source/UI/PanelArpAndFilter.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PanelArpAndFilter.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PanelEngine_3d916ae7.o: ../../../Plugin/Source/UI/PanelEngine.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PanelEngine.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PanelModulation_3a30d121.o: ../../../Plugin/Source/UI/PanelModulation.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PanelModulation.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditor_5326167c.o: ../../../Plugin/Source/PluginEditor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessor_e32f2d.o: ../../../Plugin/Source/PluginProcessor.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PreenLookAndFeel_f74a21bb.o: ../../../Plugin/Source/UI/PreenLookAndFeel.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PreenLookAndFeel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/StepSequencer_c4513266.o: ../../../Plugin/Source/UI/StepSequencer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling StepSequencer.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/exoFont_8e57ed9e.o: ../../../Plugin/Source/UI/OTF/exoFont.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling exoFont.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tinythread_3b828360.o: ../../../Plugin/Source/PluginParameters/include/tinythread/source/tinythread.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tinythread.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AudioProcessorPlayerWithMidiOutput_efdf50ae.o: ../../Source/AudioProcessorPlayerWithMidiOutput.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AudioProcessorPlayerWithMidiOutput.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Main.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_basics_6b797ca1.o: ../../JuceLibraryCode/juce_audio_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_devices_a742c38b.o: ../../JuceLibraryCode/juce_audio_devices.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_formats_5a29c68a.o: ../../JuceLibraryCode/juce_audio_formats.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_processors_dea3173d.o: ../../JuceLibraryCode/juce_audio_processors.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_audio_utils_c7eb679f.o: ../../JuceLibraryCode/juce_audio_utils.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_core_75b14332.o: ../../JuceLibraryCode/juce_core.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_cryptography_6de2ebff.o: ../../JuceLibraryCode/juce_cryptography.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_data_structures_72d3da2c.o: ../../JuceLibraryCode/juce_data_structures.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_events_d2be882c.o: ../../JuceLibraryCode/juce_events.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_graphics_9c18891e.o: ../../JuceLibraryCode/juce_graphics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_basics_8a6da59c.o: ../../JuceLibraryCode/juce_gui_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_extra_4a026f23.o: ../../JuceLibraryCode/juce_gui_extra.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_opengl_cd70b4c2.o: ../../JuceLibraryCode/juce_opengl.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
