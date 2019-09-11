all:
	@echo "Usage: make javadoc"

javadoc:
	@find . -type d -name 'src' -o -name 'TP1' |while read dir; do \
		dest="javadoc/$$(echo $$dir |sed 's/\/src//')"; \
		mkdir -p "$$dest"; \
		if ls $$dir/*.java &>/dev/null; then \
			javadoc -private -d "$$dest" -sourcepath "$$dir" "$$(cd $$dir && echo *.java)"; \
		else \
			javadoc -private -d "$$dest" -sourcepath "$$dir" -subpackages "$$(cd $$dir && echo * |sed 's/ /:/g')"; \
		fi ; \
		done

clean:
	rm -rf javadoc

.PHONY: javadoc all clean
