mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

FE6_GBA ?= ../fe6.gba

STRING_LOCATIONS := $(mkfile_dir)/string-locations.txt

STRINGS_REPOINT := $(mkfile_dir)/data/fe6-strings-repoint.event
STRINGS_SOURCES := $(mkfile_dir)/data/fe6-strings.s

$(shell mkdir -p $(mkfile_dir)/data > /dev/null)

all: $(STRINGS_REPOINT) $(STRINGS_SOURCES)
.PHONY: all

clean:
	@rm -f $(STRINGS_REPOINT) $(STRINGS_SOURCES)
.PHONY: clean

$(STRINGS_REPOINT): $(STRING_LOCATIONS) $(FE6_GBA)
	@echo "[GEN]	$@"
	@python3 tools/py/cvtstringevt.py $(FE6_GBA) $(STRING_LOCATIONS) > $(STRINGS_REPOINT)

$(STRINGS_SOURCES): $(STRING_LOCATIONS) $(FE6_GBA)
	@echo "[GEN]	$@"
	@python3 tools/py/cvtstrings.py $(FE6_GBA) $(STRING_LOCATIONS) > $(STRINGS_SOURCES)
