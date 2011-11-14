.PHONY: clean All

All:
	@echo ----------Building project:[ PrinterQueue - Debug ]----------
	@cd "PrinterQueue" && "$(MAKE)" -f "PrinterQueue.mk"
clean:
	@echo ----------Cleaning project:[ PrinterQueue - Debug ]----------
	@cd "PrinterQueue" && "$(MAKE)" -f "PrinterQueue.mk" clean
