
CC ?= gcc

PACKAGES_DIR = src
PACKAGES = commands helloworld

PACKAGE_CFLAGS = -O3 -iquote . -std=c11 -Wno-unused-result -g -fPIC
PACKAGE_LDFLAGS = -shared -fPIC
ifeq ($(shell uname), Darwin)
PACKAGE_LDFLAGS += -undefined dynamic_lookup
endif

DIST=dist
DEPLOY_DIR=/usr/local/EmojicodePackages

.PHONY: all

all: clean builds $(addsuffix .so,$(PACKAGES)) headers deploy

define package
PKG_$(1)_LDFLAGS = $$(PACKAGE_LDFLAGS)
PKG_$(1)_SOURCES = $$(wildcard $$(PACKAGES_DIR)/$(1)/*.c)
# PKG_$(1)_HEADERS = $$(wildcard $$(PACKAGES_DIR)/$(1)/*.emojic)
PKG_$(1)_OBJECTS = $$(PKG_$(1)_SOURCES:%.c=%.o)
$(1).so: $$(PKG_$(1)_OBJECTS) $$(PKG_$(1)_HEADERS)
	$$(CC) $$(PKG_$(1)_LDFLAGS) $$^ -o $(DIST)/$(1)/$$@ -iquote $$(<D)
$$(PKG_$(1)_OBJECTS): %.o: %.c
	$$(CC) $$(PACKAGE_CFLAGS) -c $$< -o $$@
# $$(PKG_$(1)_HEADERS):
# 	cp $(1).emojic $(DIST)/$(1)/$(1).emojic
endef

$(foreach pkg,$(PACKAGES),$(eval $(call package,$(pkg))))

# Make the dist folder and a folder for each packages distribution files
builds:
	mkdir -p $(DIST)
	$(foreach pkg,$(PACKAGES),mkdir -p $(DIST)/$(pkg) $(DEPLOY_DIR)/$(pkg)-v0)

# Copy the .emojic header to the dist folder
headers:
	$(foreach pkg,$(PACKAGES),cp $(PACKAGES_DIR)/$(pkg)/*.emojic $(DIST)/$(pkg)/header.emojic;)

# Copy the .so and .emojic files to /usr/local/EmojicodePackages
deploy:
	$(foreach pkg,$(PACKAGES),cp $(DIST)/$(pkg)/* $(DEPLOY_DIR)/$(pkg)-v0; ln -s /usr/local/EmojicodePackages/$(pkg)-v0 /usr/local/EmojicodePackages/$(pkg);)

clean:
	rm -rf $(DIST) $(PACKAGES_DIR)/*/*.o
	$(foreach pkg,$(PACKAGES),rm -rf $(DEPLOY_DIR)/$(pkg)*)
