package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"

	"aoc2025/utils"
)

func main() {
	fpath, err := utils.GetFpath(os.Args)
	if err != nil {
		fmt.Printf("Error getting input %s", err)
	}

	data, err := utils.ReadAsLinesNL(fpath)
	if err != nil {
		fmt.Printf("Error reading file: %s", err)
	}

	processAvailable := false
	availableItems := []string{}
	freshRange := []string{}

	for _, word := range data {
		if word == "" {
			processAvailable = true
			continue
		}

		if processAvailable {
			availableItems = append(availableItems, word)
		} else {
			freshRange = append(freshRange, word)
		}
	}

	// Items now in list
	available := []int{}

	for _, item := range availableItems {
		item, err := strconv.Atoi(item)
		if err == nil {
			available = append(available, item)
		}
	}

	itemsCount := 0
	for _, item := range available {
		if isInFreshRange(item, freshRange) {
			itemsCount++
		}
	}

	fmt.Printf("Items available from fresh stock: %d\n", itemsCount)
}

func isInFreshRange(item int, ranges []string) bool {
	for _, rangeStr := range ranges {
		limits := strings.Split(rangeStr, "-")
		start, _ := strconv.Atoi(limits[0])
		end, _ := strconv.Atoi(limits[1])

		if item >= start && item <= end {
			return true
		}
	}
	return false
}
