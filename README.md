# Set Calculator – Mathematical Set Operations in C

This project is a **set calculator** implemented in **C**, which provides various operations on mathematical sets and relations, including **union, intersection, subset checks, and relation properties**.

## 📌 Project Overview
- **Language:** C
- **Concept:** Set theory operations and relation analysis
- **Key Features:**
  - Basic set operations: **union, intersection, difference**
  - Set properties: **cardinality, complement**
  - Relation properties: **reflexivity, symmetry, antisymmetry, transitivity**
  - Function properties: **injective, surjective, bijective**
  - **Parsing from a file** for input processing

## 🔧 Supported Operations
| Operation | Description |
|-----------|------------|
| `empty A` | Checks if set `A` is empty |
| `card A` | Returns the number of elements in set `A` |
| `complement A` | Returns the complement of set `A` |
| `union A B` | Returns the union of sets `A` and `B` |
| `intersect A B` | Returns the intersection of sets `A` and `B` |
| `minus A B` | Returns the difference `A - B` |
| `subseteq A B` | Checks if `A` is a subset of `B` |
| `subset A B` | Checks if `A` is a proper subset of `B` |
| `equals A B` | Checks if sets `A` and `B` are equal |
| `reflexive R` | Checks if relation `R` is reflexive |
| `symmetric R` | Checks if relation `R` is symmetric |
| `antisymmetric R` | Checks if relation `R` is antisymmetric |
| `transitive R` | Checks if relation `R` is transitive |
| `function R` | Checks if relation `R` is a function |
| `domain R` | Returns the domain of relation `R` |
| `codomain R` | Returns the codomain of relation `R` |
| `injective R A B` | Checks if relation `R` is injective from `A` to `B` |
| `surjective R A B` | Checks if relation `R` is surjective from `A` to `B` |
| `bijective R A B` | Checks if relation `R` is bijective from `A` to `B` |

## 📁 Project Files
- `setcal.c` – C implementation of set operations
- `README.md` – Project documentation

## 🚀 How to Use
1. **Compile the program** using GCC:
   ```bash
   gcc -o setcal setcal.c
2. **Run the program**  with an input file:
   ```bash
   ./setcal input.txt
3. **Example input file** (input.txt):
   ```bash
    U a b c d
    S a b
    S c d
    C union 1 2
## 📝 Author
**Dinara Garipova**  
Project for **IZP Course**  

## ⚖️ License
This project is licensed under the **MIT License** – you are free to use, modify, and distribute with attribution.
