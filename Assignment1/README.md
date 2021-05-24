Language used: Go

Approach: Input string is taken, variable int x is appended to it. 
          Then from package sha256, encrypted array of bytes is returned.
          Hex.EncodeToString returns the hexadecimal encoding of this encryption in the form of a string.
          if this string has more than or equal to 5 0's in the beginning it implies that it is smaller than the target.
          
Some Expected outputs: 
                      
                      abc
                      Input is abc
                      x is 767150
                      Hence combination is abc767150
                      Time elapsed: 285.6863ms

                      assassin
                      Input is assassin
                      x is 1198235
                      Hence combination is assassin1198235
                      Time elapsed: 469.4712ms

                      qwerty
                      Input is qwerty
                      x is 1597159
                      Hence combination is qwerty1597159
                      Time elapsed: 617.9101ms

                      (Time elapsed may vary)
