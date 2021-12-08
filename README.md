# Binary File Manipulation in C
This project was developed by Gabriel Tetzlaf and Pedro Potenza as part of the Data Structures II course, teach by Veronica Carvalho in 2021 on UNESP.

# Getting Started
- MacOS/Ubuntu: <br>
` gcc BinaryManipulation.c` <br>
`./a.out `

- Windows: <br>
` gcc BinaryManipulation.c` <br>
`BinaryManipulation.c`

# About the result file
- Header: <br>
  - 1 int with the removed memory address
  - 1 char to save the amount of added registers
  - 1 char to save the amount of removed registers

- Register: <br>
  - First field: register size
  - Second field: Valid ($) or Invalid (*)
  - Third field: Client ID
  - Fourth field: Movie ID
  - Fifith field: Client name
  - Sixth field: Movie name
  - Seventh field: Gender

    - The fields are separates as shown below: 
      > 61$1#1#João da Silva# Indiana Jones e a Última Cruzada#Aventura

- Removal:
  - All removed information are changed to "-" 
