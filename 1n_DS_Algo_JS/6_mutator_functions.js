// Mutator functions

// 1. push() - append to array
nums.push(5);
nums // 1, 2, 3, 4, 5

// 2. unshift() - prepend to array
var nums = [2, 3, 4, 5];
nums.unshift(1); // 5
nums // 2, 3, 4

// 3. pop() - remove from the end
var nums = [1, 2, 3, 4, 5];
nums.pop() // 5
nums // 1, 2, 3, 4

// 4. shift() - remove from the beginning
nums.shift() // 1
nums // 2, 3, 4, 5 

// 5. splice(start_indiex_where_to_add, num_elements_to_remove_0_if_none, els_to_add)
var nums = [1, 2, 3, 7, 8, 9];
var newElements = [4, 5, 6];
nums.splice(3, 0, nuwElements);
nums // 1, 2, 3, 4, 5, 6, 7, 8, 9

var nums = [1,2,3,7,8,9];
nums.splice(3,0,4,5,6);

// removing elements
var nums = [1,2,3,100,200,300,400,4,5];
nums.splice(3,4); // 100, 200, 300, 400
print(nums); // 1,2,3,4,5 

// 6. reverse() - reverse the order
var nums = [1, 2, 3, 4, 5];
nums.reverse();
nums // reversed

// 5. sort() - to sort arrays
var names = ["David","Mike","Cynthia","Clayton","Bryan","Raymond"];
nums.sort();
print(nums); // Bryan,Clayton,Cynthia,David,Mike,Raymond

// But sort() does not work so well with numbers:
var nums = [3,1,2,100,4,200];
nums.sort();
print(nums); // 1,100,2,200,3,4

// To use the different approach:
// The sort() function uses the compare() function to sort the array 
// elements numerically rather than lexicographically. 
function compare(num1, num2) {
    return num1 - num2;
}
var nums = [3,1,2,100,4,200];
nums.sort(compare);
print(nums); // 1,2,3,4,100,200



