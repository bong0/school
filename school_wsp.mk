.PHONY: clean All

All:
	@echo ----------Building project:[ Inheritance_Demo - Debug ]----------
	@cd "Inheritance_Demo" && "$(MAKE)" -f "Inheritance_Demo.mk"
clean:
	@echo ----------Cleaning project:[ Inheritance_Demo - Debug ]----------
	@cd "Inheritance_Demo" && "$(MAKE)" -f "Inheritance_Demo.mk" clean
