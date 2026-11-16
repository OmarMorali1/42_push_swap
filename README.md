*This project has been created as part of the 42 curriculum by atahlawi, ommorali.*

# push_swap

## Description

push_swap sorts a list of integers using two stacks, **a** and **b**, and a small set of operations. The program prints the list of operations that leaves stack **a** sorted in ascending order (smallest on top) with stack **b** empty. The goal is to do this with as few operations as possible.

The available operations are `sa`, `sb`, `ss` (swap), `pa`, `pb` (push), `ra`, `rb`, `rr` (rotate) and `rra`, `rrb`, `rrr` (reverse rotate).

The project contains four sorting strategies of different complexity, plus a `checker` program that verifies a list of operations. Complexity is always measured in the **number of push_swap operations generated**, not in classical array-based time.

### Contributions

- **atahlawi**: checker, simple sort, medium sort, the stack operations, input parsing and validation.
- **ommorali**: complex sort, adaptive strategy selection, benchmark mode, main program, this README.
- **Both**: splitting the code across multiple files and the overall design.

## Instructions

### Compile

```bash
make          # builds push_swap
make bonus    # builds checker
make clean    # removes object files
make fclean   # removes object files and binaries
make re       # full rebuild
```

### Run

```bash
./push_swap [--bench] [--simple | --medium | --complex | --adaptive] <integers...>
```

| Flag         | Meaning                                                       |
| ------------ | ------------------------------------------------------------- |
| `--simple`   | Force the O(n²) algorithm                                     |
| `--medium`   | Force the O(n√n) algorithm                                    |
| `--complex`  | Force the O(n log n) algorithm                                |
| `--adaptive` | Pick the algorithm from the measured disorder (default)       |
| `--bench`    | Print disorder, strategy, and operation counts to **stderr**  |

Numbers may be given as separate arguments or inside quoted strings. The first number is the top of stack **a**.

```bash
$ ./push_swap 2 1 3 6 5 8
$ ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker $ARG
OK
$ ./push_swap --bench --adaptive $ARG 2> bench.txt | ./checker $ARG
OK
$ ./push_swap 3 2 3
Error
```


### Checker

```bash
$ ./checker 3 2 1 0
rra
pb
sa
rra
pa
OK
```

The checker reads operations from standard input and prints `OK` if **a** is sorted and **b** is empty, `KO` otherwise, or `Error` on stderr for invalid numbers or unknown operations.

## Algorithms

### Disorder metric

Before any move, we measure the disorder of stack **a**: the number of pairs where a bigger number appears before a smaller one, divided by the total number of pairs. It is `0` for a sorted stack and `1` for a reversed one.
### Simple: selection sort, O(n²)

Repeatedly find the smallest value in **a**, rotate it to the top using whichever of `ra` or `rra` is shorter, and push it to **b**. When two elements remain, fix them with `sa` if needed, then push everything back with `pa`.

### Medium: chunk sort, O(n√n)

The values are ranked by index and split into chunks of about √n values. We scan stack **a** and push elements that belong to the current range onto **b**. The smallest ones are rotated to the bottom of **b**, so **b** ends up roughly ordered, with the largest values near the top and the smallest near the bottom. Then we repeatedly bring the largest value of **b** to the top (using `rb` or `rrb`, whichever is shorter) and push it back with `pa`. Stacks of 2 to 5 elements use small dedicated routines.


### Complex: cost-based insertion (Turk sort), O(n log n)

1. Push all elements to **b** except three, keeping the three largest in **a** and rotating small values in **b** to improve their order. Sort the three remaining elements in **a**.
2. Repeat until **b** is empty: for every element of **b**, find its target position in **a** (the smallest value in **a** that is larger than it, or the minimum of **a** if none is) and compute the rotation cost of bringing both the element and its target to the top. When both stacks rotate in the same direction, `rr` or `rrr` handles both at once, so the cost is the larger of the two instead of the sum. Pick the **cheapest** element, rotate, and `pa`.
3. Rotate **a** so the minimum is on top.

### Adaptive (default)

The adaptive strategy measures the disorder and picks the algorithm:

| Disorder        | Algorithm        |
| --------------- | ---------------- |
| below 0.2       | Simple, O(n²)    |
| 0.2 to below 0.5| Medium, O(n√n)   |
| 0.5 and above   | Complex, O(n log n) |


### Complexity summary

| Strategy | Time (operations) | Space |
| -------- | ----------------- | ----- |
| Simple   | O(n²)             | O(n)  |
| Medium   | O(n√n)            | O(n)  |
| Complex  | O(n log n) | O(n) |
| Adaptive | O(n²) / O(n√n) / O(n log n) | O(n) |


### Measured results

Average operations over 5 random runs (values drawn from 0 to 9999):

| Strategy  | 100 numbers | 500 numbers |
| --------- | ----------- | ----------- |
| Simple    | ~1460       | ~32500      |
| Medium    | ~600        | ~5230       |
| Complex   | ~570        | ~4630       |
| Adaptive  | ~580        | ~4930       |

The default adaptive mode stays under the subject's "excellent" thresholds (700 operations for 100 numbers, 5500 for 500 numbers) in these runs.

## Resources

- Multiple YouTube channels such as 'https://youtu.be/wRvipSG4Mmk'
- Articles, GitHub and tutorials on the "Turk algorithm" and chunk-based approaches to push_swap
- The push_swap subject

### Use of AI

- Finding and describing resources.
- Testing code using edge cases.
- Looking for memory leaks.
- Suggesting test comands for easier testing.