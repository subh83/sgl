# Change these if needed or pass as input parameter
PREFIX = /usr/local

# ================================

# INCLUDE FOLDER
# --------------

SGL_FOLDER = $(PREFIX)/include

# --------------------------------------------
# Install

.PHONY: install
install:
	cp -r sgl $(SGL_FOLDER)
	find $(SGL_FOLDER)/sgl -type d -exec chmod 755 {} \;
	find $(SGL_FOLDER)/sgl -type f -exec chmod 644 {} \;

.PHONY: all
all:
	cd examples-sgl && make all

.PHONY: uninstall
uninstall:
	rm -rf $(SGL_FOLDER)/sgl
