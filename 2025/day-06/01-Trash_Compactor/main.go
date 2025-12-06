package main

import (
	"fmt"
	"log"
	"os"
	"strconv"

	"aoc2025/utils"
)

func main() {
	fpath, err := utils.GetFpath(os.Args)
	if err != nil {
		log.Fatal(err)
	}

	input, err := utils.ReadAsGridString(fpath)
	if err != nil {
		log.Fatal(err)
	}

	total := 0
	problems := utils.TransposeGridString(input)

	for _, problem := range problems {
		answer, err := strconv.Atoi(problem[0])
		if err != nil {
			log.Fatal(err)
		}
		operator := problem[len(problem)-1]

		// fmt.Print("Problem:", problem[:len(problem)-1], " Operator:", operator)

		switch operator {
		case "*":
			for _, val := range problem[1 : len(problem)-1] {
				num, err := strconv.Atoi(val)
				if err != nil {
					log.Fatal(err)
				}
				answer *= num
			}
		case "+":
			for _, val := range problem[1 : len(problem)-1] {
				num, err := strconv.Atoi(val)
				if err != nil {
					log.Fatal(err)
				}
				answer += num
			}
		}

		// fmt.Println(" Answer:", answer)
		total += answer
	}

	fmt.Println("Total:", total)
}
