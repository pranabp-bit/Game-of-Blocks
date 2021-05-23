package main

import (
	"fmt"
	"crypto/sha256"
	"time"
	"encoding/hex"
	"strconv"
)

func cnt0 (a string ) int{
	
	for index, s := range a {
        if(s!='0'){
		return index;
		}	
	}
	
	return len(a)
} 

func main() {
	var a string
	fmt.Scanln(&a)
	fmt.Println("Input is",a)
	start := time.Now()
	i:=-1
	for  {
		i=i+1
		k:=a+strconv.Itoa(i)
		hash :=sha256.Sum256([]byte (k)) 

		if cnt0( hex.EncodeToString(hash[:]))>=5{
			fmt.Println("x is",i)
			fmt.Println("Hence combination is",k)
			elapsed := time.Since(start)
			fmt.Printf("Time elapsed: %s\n", elapsed)
			return
		}
	}

}