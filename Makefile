CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I src
SRC_DIR = src
TEST_DIR = tests

# Основная программа
SOURCES = $(SRC_DIR)/main.cc $(SRC_DIR)/database.cc $(SRC_DIR)/menu.cc $(SRC_DIR)/input_utils.cc
TARGET = student_manager

# Тесты
TEST_SOURCES = $(TEST_DIR)/test_main.cc $(SRC_DIR)/database.cc $(SRC_DIR)/input_utils.cc
TEST_TARGET = run_tests

# Флаги для покрытия
COVERAGE_FLAGS = -fprofile-arcs -ftest-coverage
COVERAGE_INFO = coverage.info
COVERAGE_DIR = coverage_report

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES)

# Сборка тестов с покрытием
coverage: CXXFLAGS += $(COVERAGE_FLAGS)
coverage: test
	./$(TEST_TARGET)

# Генерация отчета покрытия
report: coverage
	@echo "📊 Генерация отчета покрытия..."
	@lcov --capture --directory . --output-file $(COVERAGE_INFO) 2>/dev/null
	@lcov --remove $(COVERAGE_INFO) '/usr/*' '*/tests/*' --output-file $(COVERAGE_INFO) 2>/dev/null
	@genhtml $(COVERAGE_INFO) --output-directory $(COVERAGE_DIR) 2>/dev/null
	@echo "✅ Отчет покрытия сгенерирован в папке: $(COVERAGE_DIR)"
	@echo "📁 Откройте: $(COVERAGE_DIR)/index.html"

# Покрытие через gcovr (более надежно)
coverage-gcovr: CXXFLAGS += $(COVERAGE_FLAGS)
coverage-gcovr: test
	./$(TEST_TARGET)
	@echo " "
	@echo "📊 Отчет покрытия (gcovr):"
	@echo "========================="
	@gcovr -r . --filter="src/.*" --exclude=".*test.*" --print-summary || echo "Установите gcovr: pip install gcovr"

# Показать отчет (после make report)
show-report:
	@if [ -d "$(COVERAGE_DIR)" ]; then \
		echo "📂 Открываю отчет покрытия..."; \
		xdg-open "$(COVERAGE_DIR)/index.html" 2>/dev/null || open "$(COVERAGE_DIR)/index.html" 2>/dev/null || start "$(COVERAGE_DIR)/index.html" 2>/dev/null || echo "📁 Откройте вручную: $(COVERAGE_DIR)/index.html"; \
	else \
		echo "❌ Сначала выполните: make report"; \
	fi

clean:
	rm -f $(TARGET) $(TEST_TARGET) *.txt
	rm -f *.gcno *.gcda *.gcov
	rm -f $(COVERAGE_INFO)
	rm -rf $(COVERAGE_DIR)

.PHONY: all test coverage report coverage-quick show-report clean