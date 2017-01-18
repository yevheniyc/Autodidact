// Inerator Functions

// 1. Non-Array-Generating Interator Functions


// - forEach()
function square(num) {
    console.log(num, num * num);
}
var nums = [1,2,3,4,5,6,7,8,9,10];
nums.forEach(square);
/*
1 1
2 4
3 9
4 16 ...
*/

// - every()
function isEven(num) {
    return num % 2 == 0;
}

var nums = [2,4,6,8,10];
var even = nums.every(isEven);
if (even) {
    print("all numbers are even");
}
else {
    print("not all numbers are even");
}

// The program displays:
all numbers are even
// If we change the array to:
var nums = [2,4,6,7,8,10];
// the program displays:
not all numbers are even

// - some() - works in similar matter but with some or none

// - reduce() - applies a function to an accumulator and the successive elements
// of an array until the end of the array is reached, yielding a single value. 
function add(runningTotal, currentValue) {
    return runningTotal + currentValue;
}
var nums = [1,2,3,4,5,6,7,8,9,10];
var sum = nums.reduce(add);

// The reduce() function, in conjunction with the add() function, works from left to right,
// computing a running sum of the array elements, like this:
add(1,2) -> 3
add(3,3) -> 6
add(6,4) -> 10
add(10,5) -> 15
add(15,6) -> 21
add(21,7) -> 28
add(28,8) -> 36
add(36,9) -> 45
add(45,10) -> 55

// We can also use reduce() with strings to perform concatenation:
function concat(accumulatedString, item) {
    return accumulatedString + item;
}
var words = ["the ", "quick ","brown ", "fox "];
var sentence = words.reduce(concat);
console.log(sentence); // displays "the quick brown fox"

// JavaScript also provides a reduceRight() function, which works similarly to re
// duce(), only working from the righthand side of the array to the left, instead of from
// left to right. The following program uses reduceRight() to reverse the elements of an array:
function concat(accumulatedString, item) {
    return accumulatedString + item;
}
var words = ["the ", "quick ","brown ", "fox "];
var sentence = words.reduceRight(concat);
console.log(sentence); // displays "fox brown quick the"


// Iterator Functions that Return a New Array - map() and filter()

// map() - works similar to forEach(), applying a function to each element of an array. The map() function, however, return a new array with the results of the funciton applications
function curve(grade) {
    grade += 5;
}
var grades = [77, 65, 81, 92, 83];
var newGrades = grades.map(curve);
console.log(newGrades); // 82, 70, 86, 97, 88

// map() - generating acronym
function first(word) {
    return word[0];
}
var words = ["for","your","information"];
var acronym = words.map(first);
print(acronym.join("")); // displays "fyi"


