ifndef _COMMON_MK
unexport _COMMON_MK := 1

# TODO The warning below should become an error after a few nightly builds.
ifneq (,$(filter 3.7% 3.80,$(MAKE_VERSION)))
$(warning $(MAKE): Error: version $(MAKE_VERSION) too old, 3.81+ required)
endif

# Generates a rule to run ClmCompiler iff the XML exists.
# USAGE: $(call GenClmCompilerRule,target-dir,src-base[,flags[,ext]])
#   This macro relies on GNU make's eval function to generate an
# explicit rule to generate a particular CLM data file each time
# it's called. Make variables which should be evaluated during eval
# processing get one $, those which should defer till "runtime" get two.
#   The CLM "base flags" are the default minimal set, the "ext flags"
# are those which must be present for all released builds.
# The "clm_compiled" phony target is provided for makefiles which need
# to defer some other processing until CLM data is ready, and "clm_clean"
# and "CLM_DATA_FILES" make it easier for client makefiles to clean up CLM data.
#   The outermost conditional allows this rule to become a no-op
# in external settings where there is no XML input file while allowing
# it to turn back on automatically if an XML file is provided.
#   Vpath is used to find the XML input because this file is not allowed
# to be present in external builds. Use of vpath allows it to be "poached"
# from the internal build if necessary.
#   There are a few ways to set ClmCompiler flags: passing them as the $3
# parameter (preferred) or by overriding CLMCOMPDEFFLAGS. Additionally,
# if the make variable CLM_TYPE is defined it points to a config file
# for the compiler. The CLMCOMPEXTFLAGS variable contains "external flags"
# which must be present for all external builds. It can be forced to "" for
# debug builds.
#   The undocumented $5 parameter has been used for dongle testing
# against variant XML but its semantics are subject to change.
CLMCOMPDEFFLAGS ?= --region '\#a/0' --region '\#r/0' --full_set
CLMCOMPEXTFLAGS  := --obfuscate
define GenClmCompilerRule
$(eval\
.PHONY: clm_compiled clm_clean
ifneq (,$(wildcard $(addsuffix /wl/clm/private/wlc_clm_data.xml,$2 $2/../../src $2/../../../src)))
  vpath wlc_clm_data.xml $(addsuffix /wl/clm/private,$5 $2 $2/../../src $2/../../../src)
  $1/wlc_clm_data$4.c: wlc_clm_data.xml ; \
    $$(strip $$(abspath $$(<D)/../../../tools/build/ClmCompiler) \
      $$(if $$(CLM_TYPE),--config_file $$(abspath $$(<D)/../types/$$(CLM_TYPE).clm) $3,$$(if $3,$3,$$(CLMCOMPDEFFLAGS))) \
      $(CLMCOMPEXTFLAGS) $$< $$@)
  clm_compiled: $1/wlc_clm_data$4.c
  clm_clean:: ; $$(RM) $1/wlc_clm_data$4.c
  CLM_DATA_FILES += $1/wlc_clm_data$4.c
else
  clm_compiled:
  clm_clean::
endif
)
endef

endif	# _COMMON_MK
