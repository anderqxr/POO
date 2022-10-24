## @040 Estressados B: Contagem

![cover](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/040/cover.jpg)

[](toc)

- [Intro](#intro)
- [Guide](#guide)
- [Shell](#shell)
[](toc)

***

## Intro

- **count**: quantas vezes o valor X apareceu na fila?
- **sum**: qual a soma de todos os valores de stress da fila?
- **average**: qual a média de stress?
- **half_compare**: qual metade da lista é mais estressada? A primeira metade ou a segunda metade? A quantidade de elementos na lista sempre será par. [draw, first, second]
- **more_men_or_women**: existem mais homens ou mulheres? [draw, men, women]
- **sex_battle**: quem é mais estressado em média? [draw, men, women]

## Guide

- [solver.cpp](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/040/.cache/draft.cpp), [aux.hpp](https://raw.githubusercontent.com/senapk/cppaux/master/aux.hpp)
- [solver.js](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/040/.cache/draft.js)
- [solver.ts](https://raw.githubusercontent.com/qxcodepoo/arcade/master/base/040/.cache/draft.ts)

## Shell

```sh
#__case count
$count [5,3,-1,-50,-1,-99] -1
2
$count [-1,-50,-1,-99,-444] 10
0
$end
========
```

```sh
#__case sum
$sum [1,-1]
2
$sum [5,3,-1]
9
$sum [-1,-50]
51
$end
========
```



```sh
#__case average
$average [5,3,-1,-50,-1,-99]
26.50
$average [-1,-50,-1,-99,-444]
119.00
$end
```

```sh
#__case more_men
$more_men [5,3,1,-50,-1,-99]
draw
$more_men [5,-3,1,-50,-1,-99]
women
$more_men [5,3,1,-50,-1,99]
men
$end
```

```sh
#__case half_compare
$half_compare [5,-5]
draw
$half_compare [5,-4]
first
$half_compare [5,-6]
second
$half_compare [5,3]
first
$half_compare [3,5]
second
$half_compare [5,3,-1,50,10,-999]
second
$half_compare [50,-98,2,-50,-1,-99]
draw
$half_compare [51,99,1,-50,-1,-99]
first
$end
```

```sh
#__case sex_battle
$sex_battle [5,3,-1,-50,-10,-999]
women
$sex_battle [50,98,2,-50,-1,9991]
men
$sex_battle [-50,99,1,50,-1,-99]
draw
$end
```