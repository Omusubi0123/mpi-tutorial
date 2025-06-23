# 拡張子とコンパイラの対応
compile:
	@src="$(FILE)"; \
	if [ -z "$$src" ]; then echo "Usage: make compile FILE=path/to/file.c"; exit 1; fi; \
	ext=$${src##*.}; \
	dir=$$(dirname "$$src"); \
	base=$$(basename "$$src" .$$ext); \
	bindir="$$dir/bin"; \
	mkdir -p "$$bindir"; \
	case "$$ext" in \
		c) compiler=mpicc ;; \
		cc|cpp) compiler=mpicxx ;; \
		f90) compiler=mpif90 ;; \
		*) echo "Unsupported extension: $$ext"; exit 1 ;; \
	esac; \
	echo "Compiling $$src → $$bindir/$$base using $$compiler"; \
	$$compiler "$$src" -o "$$bindir/$$base"

# 実行
run:
	@src="$(FILE)"; \
	if [ -z "$$src" ]; then echo "Usage: make run FILE=path/to/file.c [NP=4]"; exit 1; fi; \
	ext=$${src##*.}; \
	dir=$$(dirname "$$src"); \
	base=$$(basename "$$src" .$$ext); \
	exe="$$dir/bin/$$base"; \
	if [ ! -f "$$exe" ]; then echo "Executable $$exe not found. Run 'make compile FILE=$$src' first."; exit 1; fi; \
	np=$${NP:-4}; \
	echo "Running $$exe with $$np processes"; \
	mpirun -np "$$np" "$$exe"

# クリーン
clean:
	find . -type d -name bin -exec rm -rf {} +
