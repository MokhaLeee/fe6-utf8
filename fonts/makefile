# FONT_LIST ?= FontList-cn.txt
FONT_LIST ?= FontList-en.txt

EXE :=
PYTHON3 := python3

ifeq ($(strip $(DEVKITPRO)),)
	$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitpro)
endif

GRIT := $(DEVKITPRO)/tools/bin/grit$(EXE)

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))

GLYPH_DEPS := $(mkfile_dir)$(FONT_LIST)

GLYPH_GENERATOR := $(PYTHON3) $(mkfile_dir)Scripts/glyph-installer-generator.py
GLYPH_INSTALLER := $(mkfile_dir)GlyphInstaller.event

$(GLYPH_INSTALLER): $(GLYPH_DEPS)
	@echo "[GEN]	$@"
	@$(GLYPH_GENERATOR) -i $<

CLEAN_FILES += $(GLYPH_INSTALLER)

%_font.img.bin: %_font.png
	@echo "[GEN]	$@"
	@$(GRIT) $< -gB2 -p! -tw16 -th16 -ftb -fh! -o $@

CLEAN_DIRS  += $(mkfile_dir)build

clean:
	@rm -f $(CLEAN_FILES)
	@rm -rf $(CLEAN_DIRS)
