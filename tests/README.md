# Tests Directory

This directory contains unit tests and integration tests for the PaperFlip-Reader project.

## Structure
- `unit/` - Unit tests for individual components
- `integration/` - Integration tests for component interactions
- `fixtures/` - Test data and sample files

## Running Tests
Tests can be run using CMake's built-in testing framework or with a testing framework like Google Test.

## Adding New Tests
1. Create test files in appropriate subdirectories
2. Add test executables to CMakeLists.txt
3. Register tests with CMake's testing framework