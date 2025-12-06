package main

import (
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"

	"aoc2025/utils"
)

type itemRange struct {
	start int
	end   int
}

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
	freshRange := []string{}
	for _, word := range data {
		if word == "" {
			processAvailable = true
			continue
		}

		if !processAvailable {
			freshRange = append(freshRange, word)
		}
	}

	freshCount := 0
	mergedRanges := mergeRanges(parseRanges(freshRange))
	for _, item := range mergedRanges {
		freshCount += item.end - item.start + 1
	}

	fmt.Printf("Fresh count: %d\n", freshCount)
}

func parseRanges(rangeStrs []string) []itemRange {
	ranges := make([]itemRange, 0, len(rangeStrs))
	for _, rangeStr := range rangeStrs {
		limits := strings.Split(rangeStr, "-")
		start, _ := strconv.Atoi(limits[0])
		end, _ := strconv.Atoi(limits[1])
		ranges = append(ranges, itemRange{start: start, end: end})
	}
	return ranges
}

func mergeRanges(ranges []itemRange) []itemRange {
	if len(ranges) == 0 {
		return ranges
	}

	sort.Slice(ranges, func(i, j int) bool { return ranges[i].start < ranges[j].start })

	mergedRanges := []itemRange{ranges[0]}
	for i := 1; i < len(ranges); i++ {
		last := &mergedRanges[len(mergedRanges)-1]
		current := ranges[i]

		if current.start <= last.end+1 {
			if current.end > last.end {
				last.end = current.end
			}
		} else {
			mergedRanges = append(mergedRanges, current)
		}
	}
	return mergedRanges
}
