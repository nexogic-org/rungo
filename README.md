# Rungo

Rungo is the official and dedicated package manager for the **Korelin** development ecosystem. It streamlines package installation, management, project initialization, and version control for developers working with the Korelin programming language.

## Features

- **Project Initialization**: Quickly scaffold new Korelin projects with best-practice directory structures.
- **Dependency Management** (In Development): Install, uninstall, and list packages.
- **Template Support**: Support for various project templates including standard applications, plugins, and frameworks.
- **Cross-Platform**: Built with modern C++ for performance and portability.

## Installation

### Prerequisites
- C++ Compiler supporting C++20
- CMake (Version 4.1 or higher)

### Build from Source

```bash
# Clone the repository
git clone https://github.com/nexogic-org/rungo.git
cd rungo

# Build using CMake
cmake -B build
cmake --build build
```

The executable `rungo` will be located in the `bin/` directory.

## Usage

### Initialize a New Project

To create a new Korelin project:

```bash
rungo init <project-name>
```

This will generate a project structure containing:
- `project.json`: Project configuration.
- `src/main.kri`: Entry point for your application.
- `rungo_modules/`: Directory for dependencies.

### Other Commands (Coming Soon)

- `rungo install <package>`: Install a dependency.
- `rungo uninstall <package>`: Remove a dependency.
- `rungo list`: List installed packages.

## License

MIT License. See LICENSE file for details.
