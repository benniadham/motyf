## Motyf Syntax Diagram

In the syntax notation used in this documentation, syntactic categories, i.e. nonterminals, are indicated by pairs of square brackets surrounding the terms `[term]`, and literal words and character set members, i.e. terminals, are written as is or are indicated by pairs of chevrons surrounding the terms `<term>`. A colon followed by an equal sign `:=` following a nonterminal introduces its definition.

```
motyf               := [module-declaration] [imports] [definitions]

module-declaration  := module [module-name] <nl>

imports             := import [import-name] <nl>
                     | import [import-name] <nl> [imports]

module-name         := <id>
                     | <id> . [module-name]

import-name         := <id>
                     | <id> . [import-name]

definitions         := [type-definition] [definitions]
                     | [function-definition] [definitions]

type-definition     := type [class-definition]
```
