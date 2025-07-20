# Contributing to PaperFlip-Reader

Thank you for your interest in contributing to PaperFlip-Reader! This document provides guidelines and information for contributors.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
- [Development Setup](#development-setup)
- [Development Workflow](#development-workflow)
- [Coding Standards](#coding-standards)
- [Testing](#testing)
- [Pull Request Process](#pull-request-process)
- [Issue Reporting](#issue-reporting)
- [Documentation](#documentation)

## Code of Conduct

We are committed to providing a welcoming and inclusive environment for all contributors. Please be respectful, constructive, and collaborative in all interactions.

## Getting Started

### Prerequisites

- **Git**: Latest version
- **CMake**: 3.16 or higher
- **Qt**: 5.12+ or 6.x development tools
- **C++17** compatible compiler
- **Git LFS** (for large files like screenshots)

### Fork and Clone

1. **Fork the repository** on GitHub
2. **Clone your fork**:
   ```bash
   git clone https://github.com/YOUR_USERNAME/PaperFlip-Reader.git
   cd PaperFlip-Reader
   ```

3. **Add upstream remote**:
   ```bash
   git remote add upstream https://github.com/original/PaperFlip-Reader.git
   ```

## Development Setup

### 1. Environment Setup

```bash
# Initialize submodules
git submodule update --init --recursive

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

### 2. IDE Setup

#### Qt Creator
1. Open `CMakeLists.txt` as a project
2. Select appropriate Qt kit
3. Build and run

#### Visual Studio Code
1. Install extensions:
   - CMake Tools
   - C/C++
   - Qt for Python
2. Configure `.vscode/settings.json`:
   ```json
   {
     "cmake.buildDirectory": "${workspaceFolder}/build",
     "cmake.configureArgs": ["-DCMAKE_BUILD_TYPE=Debug"]
   }
   ```

#### CLion
1. Open project root directory
2. CLion will auto-detect CMake configuration
3. Configure toolchain if needed

### 3. Development Tools

- **Code Formatting**: Use provided `.clang-format`
- **Static Analysis**: Enable in your IDE
- **Debugging**: Use Qt Creator debugger or GDB/LLDB

## Development Workflow

### 1. Branch Strategy

- `main`: Production-ready code
- `develop`: Integration branch for features
- `feature/*`: New features
- `bugfix/*`: Bug fixes
- `hotfix/*`: Critical fixes

### 2. Making Changes

1. **Create feature branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

2. **Make atomic commits**:
   ```bash
   git add -p
   git commit -m "feat: add pagination support"
   ```

3. **Keep branch updated**:
   ```bash
   git fetch upstream
   git rebase upstream/main
   ```

### 3. Commit Message Format

Follow [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <description>

[optional body]

[optional footer]
```

**Types**:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation
- `style`: Code style
- `refactor`: Code refactoring
- `test`: Adding tests
- `chore`: Maintenance

**Examples**:
```
feat(ui): add dark mode toggle
fix(core): resolve EPUB parsing issue with special characters
docs: update installation instructions
```

## Coding Standards

### C++ Guidelines

- **Standard**: C++17
- **Style**: Follow [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- **Formatting**: Use provided `.clang-format`

#### Code Style Example

```cpp
// Good
class EPUBManager : public QObject {
    Q_OBJECT

public:
    explicit EPUBManager(QObject* parent = nullptr);
    ~EPUBManager() override;

    bool loadEPUB(const QString& filePath);
    QString getContent() const;

signals:
    void loadProgress(int progress);
    void loadComplete();

private:
    std::unique_ptr<EPUBParser> m_parser;
    QString m_currentFile;
};

// Bad
class EPUBManager:public QObject{
    Q_OBJECT
public:
    EPUBManager(QObject *parent=nullptr);
    bool loadEPUB(QString filePath);
};
```

### Qt-Specific Guidelines

- **Signals/Slots**: Use new signal/slot syntax
- **Memory Management**: Prefer smart pointers
- **UI Design**: Follow Qt Design Guidelines
- **Internationalization**: Use `tr()` for all user-visible strings

### File Organization

```
src/
├── core/           # Core business logic
├── ui/            # User interface
├── utils/         # Utility functions
└── main.cpp       # Application entry
```

### Naming Conventions

- **Classes**: PascalCase (`EPUBManager`)
- **Functions**: camelCase (`loadEPUB`)
- **Variables**: camelCase (`filePath`)
- **Constants**: UPPER_CASE (`MAX_FILE_SIZE`)
- **Files**: lowercase with underscores (`epub_manager.cpp`)

## Testing

### Test Structure

- **Unit Tests**: `tests/unit/`
- **Integration Tests**: `tests/integration/`
- **UI Tests**: `tests/ui/`

### Running Tests

```bash
# Build tests
cmake .. -DBUILD_TESTS=ON
cmake --build . --config Debug

# Run all tests
ctest

# Run specific test
./tests/unit/test_epub_manager
```

### Writing Tests

Use Google Test framework:

```cpp
TEST(EPUBManagerTest, LoadValidEPUB) {
    EPUBManager manager;
    EXPECT_TRUE(manager.loadEPUB("test.epub"));
    EXPECT_FALSE(manager.getContent().isEmpty());
}
```

## Pull Request Process

### 1. Before Submitting

- [ ] Code compiles without warnings
- [ ] All tests pass
- [ ] Code follows style guidelines
- [ ] Documentation updated
- [ ] Commit messages are clear

### 2. PR Requirements

- **Title**: Clear, descriptive summary
- **Description**: Explain what and why
- **Testing**: Describe how you tested
- **Screenshots**: For UI changes
- **Breaking Changes**: Document any API changes

### 3. Review Process

1. **Automated Checks**:
   - CI/CD pipeline
   - Code formatting
   - Static analysis

2. **Code Review**:
   - At least one maintainer approval
   - Address all feedback
   - Resolve conversations

3. **Merge**:
   - Squash commits if needed
   - Update changelog
   - Tag release if applicable

## Issue Reporting

### Bug Reports

Use the bug report template:

```markdown
**Bug Description**
Clear description of the issue

**Steps to Reproduce**
1. Step 1
2. Step 2
3. Step 3

**Expected Behavior**
What should happen

**Actual Behavior**
What actually happens

**Environment**
- OS: [e.g., Windows 11]
- Qt Version: [e.g., 6.5.0]
- PaperFlip-Reader Version: [e.g., 0.1.0]

**Screenshots**
If applicable
```

### Feature Requests

Use the feature request template:

```markdown
**Feature Description**
Clear description of the proposed feature

**Use Case**
Why is this feature needed?

**Proposed Solution**
How should it work?

**Alternatives**
Other solutions considered

**Additional Context**
Any other relevant information
```

## Documentation

### Code Documentation

- **Doxygen**: Use Doxygen comments for public APIs
- **README**: Update for new features
- **Examples**: Provide usage examples

### Documentation Standards

```cpp
/**
 * @brief Loads an EPUB file
 * @param filePath Path to the EPUB file
 * @return true if successful, false otherwise
 * @note This function is thread-safe
 * @see saveEPUB()
 */
bool loadEPUB(const QString& filePath);
```

## Performance Guidelines

- **Profiling**: Use Qt Creator's profiler
- **Memory**: Avoid memory leaks, use RAII
- **Responsiveness**: Keep UI responsive
- **File I/O**: Use async operations for large files

## Security Considerations

- **File Validation**: Validate all file inputs
- **Path Handling**: Use safe path operations
- **Memory Safety**: Avoid buffer overflows
- **Updates**: Support secure update mechanisms

## Release Process

### Versioning

Follow [Semantic Versioning](https://semver.org/):
- **MAJOR**: Breaking changes
- **MINOR**: New features
- **PATCH**: Bug fixes

### Release Checklist

- [ ] Update version in CMakeLists.txt
- [ ] Update CHANGELOG.md
- [ ] Create release notes
- [ ] Tag release
- [ ] Build binaries
- [ ] Update documentation

## Getting Help

- **Discord**: [Join our Discord](https://discord.gg/paperflip)
- **Discussions**: GitHub Discussions
- **Issues**: GitHub Issues
- **Email**: maintainers@paperflip-reader.org

## Recognition

Contributors are recognized in:
- **CONTRIBUTORS.md**: List of all contributors
- **Release notes**: Significant contributions
- **README.md**: Core team members

---

Thank you for contributing to PaperFlip-Reader! Your efforts help make reading better for everyone.