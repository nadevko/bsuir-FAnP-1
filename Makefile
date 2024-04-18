DESTDIR ?= dist
LABS ?= $(foreach lab,$(filter-out dist/,$(sort $(dir $(wildcard */)))),$(lab:/=))

CC ?= gcc
CXX ?= g++
CFLAGS ?= -pedantic-errors -Wall -Wextra -Werror -Ofast
CXXFLAGS ?= $(CFLAGS)

CCS := $(foreach lab,$(LABS),$(wildcard $(lab)/*.cc))
OUTS := $(foreach cc,$(CCS),$(DESTDIR)/$(basename $(cc)))
PDFS := $(foreach lab,$(LABS),$(DESTDIR)/report/lr-$(lab).pdf)

### Phony ######################################################################

.PHONY: all run-% clean clean-% dist dist-%

all: $(DESTDIR)

clean: clean-dist clean-build

clean-dist:
	@rm --verbose --recursive --force $(DESTDIR)

clean-build:
	@rm --verbose --recursive --force $(foreach lab,$(LABS),$(lab)/build $(lab)/_minted-* $(lab)/svg-inkscape)

### Build general ##############################################################

define mk-dir =
$(DESTDIR)/$(1)/:
	@mkdir --verbose --parent $(DESTDIR)/$(1)/
endef

$(DESTDIR): $(OUTS) $(PDFS)

### Build and run code #########################################################

define mk-lab =
$(DESTDIR)/$(basename $(1)): | $(DESTDIR)/$(dir $(1)) $(1)
	$(CXX) $(CXXFLAGS) -o $(DESTDIR)/$(basename $(1)) $(1)

run-$(basename $(1)): $(DESTDIR)/$(basename $(1))
	./$(DESTDIR)/$(basename $(1))
endef

$(foreach lab,$(LABS),$(eval $(call mk-dir,$(lab))))

$(foreach cc,$(CCS),$(eval $(call mk-lab,$(cc))))

### Build reports ##############################################################

define mk-report =
$(1)/build/report.pdf: $(1)/report.tex
	-cd $(1) && latexmk -synctex=1 -interaction=nonstopmode -file-line-error -xelatex -shell-escape -outdir=build -f report.tex

$(DESTDIR)/report/lr-$(1).pdf: | $(DESTDIR)/report/ $(1)/build/report.pdf
	@cp --verbose $(1)/build/report.pdf $(DESTDIR)/report/lr-$(1).pdf
endef

$(eval $(call mk-dir,report))

$(foreach lab,$(LABS),$(eval $(call mk-report,$(lab))))
