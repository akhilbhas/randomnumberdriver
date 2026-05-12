all:
	$(MAKE) -C src
	$(MAKE) -C test

clean: 
	@echo "Use component-specific clean targets"
driver_clean:
	$(MAKE) -C src clean
test_clean:
	$(MAKE) -C test clean

driver:
	$(MAKE) -C src

test:
	$(MAKE) -C test

.PHONY: all clean driver test driver_clean test_clean