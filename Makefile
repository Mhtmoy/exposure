# Directory that contains this project
PROJECT_DIR =
PROJECT = exposure
GTEST = test_$(PROJECT)

# Compilation command and flags
CXX=g++
CXXVERSION= -std=c++11
CXXFLAGS= $(CXXVERSION) -g -fprofile-arcs -ftest-coverage
LINKFLAGS= -lgtest -lpthread

# Directories
SRC_DIR = src
GTEST_DIR = test
SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

# Tool varialbes
GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint.py

DOXY_DIR = docs/code

# Default goal, used by Atom for local compilation
.DEFAULT_GOAL := tests

# default rule for compiling .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean up all files that should NOT be submitted
.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(GTEST_DIR)/output/*.dat \
	*.gcov *.gcda *.gcno *.orig ???*/*.orig \
	$(PROJECT) $(COVERAGE_RESULTS) \
	$(GTEST) $(MEMCHECK_RESULTS) $(COVERAGE_DIR)  \
	$(DOXY_DIR)/html obj bin $(PROJECT).exe $(GTEST).exe

# compilation using the files in include, src, and test, but not src/project
$(GTEST): $(GTEST_DIR)/*.cpp $(SRC_DIR)/*.cpp
	$(CXX) $(CXXFLAGS) -o $(GTEST) $(INCLUDE) \
	$(GTEST_DIR)/*.cpp $(SRC_DIR)/*.cpp $(LINKFLAGS)

.PHONY: tests
  tests: $(GTEST)

# To perform all tests
.PHONY: allTests
	allTests: $(GTEST) memcheck coverage docs static style

.PHONY: memcheck
memcheck: $(GTEST)
	valgrind --tool=memcheck --leak-check=yes $(GTEST)

.PHONY: fullmemcheck
fullmemcheck: $(GTEST)
	valgrind --tool=memcheck --leak-check=full $(GTEST)

.PHONY: coverage
coverage: $(GTEST)
	./$(GTEST)
	# Determine code coverage
	$(LCOV) --capture --gcov-tool $(GCOV) --directory . --output-file $(COVERAGE_RESULTS) --rc lcov_branch_coverage=1
	# Only show code coverage for the source code files (not library files)
	$(LCOV) --extract $(COVERAGE_RESULTS) */$(SRC_DIR)/* -o $(COVERAGE_RESULTS) --rc lcov_branch_coverage=1
	#Generate the HTML reports
	genhtml $(COVERAGE_RESULTS)  --output-directory $(COVERAGE_DIR) --rc lcov_branch_coverage=1
	#Remove all of the generated files from gcov
	rm -f *.gcda *.gcno

.PHONY: static
static: ${SRC_DIR} ${GTEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} ${GTEST_DIR} ${SRC_INCLUDE} --suppress=missingInclude

.PHONY: style
style: ${SRC_DIR} ${GTEST_DIR} ${SRC_INCLUDE} ${PROJECT_SRC_DIR}
	${STYLE_CHECK} ${SRC_DIR}/* ${GTEST_DIR}/* ${SRC_INCLUDE}/*

.PHONY: docs
docs: ${SRC_INCLUDE}
	doxygen $(DOXY_DIR)/doxyfile
