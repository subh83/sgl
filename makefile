# Change these if needed or pass as input parameter
# PREFIX = /usr/local

# ================================

# INCLUDE FOLDER
# --------------

ifneq ("$(PREFIX)","")
    SGL_FOLDER = $(PREFIX)/include
else
    SGL_FOLDER = /usr/local/include
endif

# --------------------------------------------
# Install

.PHONY: install
install:
	cp -r sgl $(SGL_FOLDER)
	find $(SGL_FOLDER)/sgl -type d -exec chmod 755 {} \;
	find $(SGL_FOLDER)/sgl -type f -exec chmod 644 {} \;


.PHONY: uninstall
uninstall:
	rm -rf $(SGL_FOLDER)/sgl
