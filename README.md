# Attributes

**Attributes** is a C++ library that provides a collection of standard attributes, each paired with a corresponding Qt widget for editing their values. This library is designed to streamline the management of various data types in applications.

![Screenshot_2024-10-09_17-12-43](https://github.com/user-attachments/assets/30545098-55f0-40d9-b4ef-9dc094523f82)

This library is currently used in the [Hesiod](https://github.com/otto-link/Hesiod) GUI, a node-based system for heightmap generation, to manage and edit node attributes.

## Features

- **Standardized Attributes**: Includes a wide range of built-in attributes (e.g., `BoolAttribute`, `IntAttribute`, `FloatAttribute`, `StringAttribute`, etc.).
- **Qt Integration**: Each attribute is linked to a corresponding Qt widget for value editing.
- **Validation and Events**: Provides support for value change events.

## Installation

1. Clone the repository:

   ```bash
   git clone git@github.com:otto-link/Attributes.git
   cd Attributes
   ```

2. Add the library to your project by including the necessary files and linking with Qt:

   ```cmake
   # Attributes
   set(ATTRIBUTES_ENABLE_TESTS OFF)
   add_subdirectory(Attributes)

   target_link_libraries(${PROJECT_NAME}
       PRIVATE attributes)
   ```

4. Ensure your project is set up to use **C++20**:

   ```cmake
   set(CMAKE_CXX_STANDARD 20)
   ```

5. Make sure to link against Qt and any other required libraries.

## Usage

### Basic Example

```cpp
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>

#include "attributes.hpp"
#include "attributes/widgets/attributes_widget.hpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QWidget window;
  window.setWindowTitle("Attributes Demo");

  attr::BoolAttribute bool_attr(true, "Enable Feature");
  attr::IntAttribute  int_attr(1, 0, 100, "Integer"); // in [0, 100]

  QVBoxLayout layout;

  layout.addWidget(attr::get_attribute_widget(&bool_attr));
  layout.addWidget(attr::get_attribute_widget(&int_attr));

  window.setLayout(&layout);
  window.show();

  return app.exec();
}
```

## Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request with your changes.

## License

This project is licensed under the GNU General Public License v3.0. See the `LICENSE` file for details.
