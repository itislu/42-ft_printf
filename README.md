# A recreation of parts of the printf function, including correct behaviour for undefined situations.

## It matches the output exactly for all combinations of the following implementations:

### After writing a '%' sign, the following specifiers are supported:
- '**c**' - A single character.
- '**s**' - A string.
- '**p**' - A pointer (as a hexadecimal address).
- '**d**' - An integer in decimal format.
- '**i**' - An integer in decimal format.
- '**u**' - An unsigned integer in decimal format.
- '**x**' - An unsigned integer in hexadecimal format with lowercase letters.
- '**X**' - An unsigned integer in hexadecimal format with uppercase letters.
- '**%**' - To just print a percent sign.

### Additionally, the following flags can be added in any order between the '%' and the specifier:
- '**#**' - Prepend "0x"/"0X" for x/X specifier, respectively.
- '**+**' - Always print the sign for signed integers. Overrides a space flag.
- ' ' - If no plus flag is given, print a space in front of signed integers.
- '**-**' - Left-justify. Overrides a 0 flag.
- '**0**' - Instead of spaces, pad the value with zeros.

### Following the flags, a width can be given:
- **number**, or '**\***' - The minimum number of characters to be printed.
  - If the conversion prints less, the rest will be printed as padding with spaces to the left of the value by default. This can be adjusted with the flags.

### After or instead of width, a precision can be given:
- '**.**', followed by a **number**, or '**\***' - The minimum number of digits to be printed for number conversions, or the maximum number of characters to be printed from a string.
  - Just a dot is taken as a precision of 0.

**For both width and precision, a '*' can be placed instead so the value will be taken from the next argument.**
