// 5! = 1 * 2 * 3 * 4 * 5
console.log(`
=====Factorial with For====
`);
function factorial(num) {
    var product = 1;
    for (var i = 1; i <= num; ++i) {
        product *= i;
    }
    return product
}

console.log(factorial(5));


console.log(`
=====Recursive Factorial====
`);

function factorial_rec(num) {
    if (num == 1) {
        return num;
    } else {
        return num * factorial(num -1);
    }
}

console.log(factorial_rec(5));
