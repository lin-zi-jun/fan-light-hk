.PHONY: clean All

All:
	@echo "----------Building project:[ KKwheel - BuildSet ]----------"
	@cd "C:\Users\Alex\Desktop\KKwheel_20490809" && make -f  "KKwheel.mk"
clean:
	@echo "----------Cleaning project:[ KKwheel - BuildSet ]----------"
	@cd "C:\Users\Alex\Desktop\KKwheel_20490809" && make -f  "KKwheel.mk" clean
