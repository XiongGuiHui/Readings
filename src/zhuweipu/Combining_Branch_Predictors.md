Combining Branch Predictors
===========================

Abstract
--------

#### instruction-level parallelism：key factor of computer performance

#### conditional branch：critical limit to instruction-level parallelism

#### predictiing condition branch：uses the history of previous branches

#### a method：combining the advantages of serveral predictors

 uses a history mechanism

 hasing branch history with branch address

 outperforms previous approach

 accuracy reaches 98.1% 

 a factor of two smaller than other schemes for the same accuracy

Introduction
------------

### branch instructions are important

#### Reason1：instruction level parallelism is used for a higher levels of performance

#### Reason2：supersclar and superpipelining techniques are popular

#### Reason3：branch instructions are important in determining overall machine performance

### compiler assisted techniques are less appropriate

#### Reason1：the number of delay slots increases

#### Reason2：the use of delay slot problematic 

##### multiple implementations of an architeccture with different superscalar or superpiplining

#### Efftect：increase the importance of hardware methods of reducing brach cost

### branch performance problem 

#### prediction of the branch direction：the theme of this paper

#### minimal delay to get the branch target 

##### Branch Target Buffer：a special instruction cache to store target instruction

##### referred to Lee and Smith for more information

### hardware branch prediction stratedies

#### bimodal branch prediction

#### local branch prediciton

#### global branch prediction

### a new technique：combines the advantage of different branch predictors 

### a method ：increases the utility of branch history by hasing it together with the branch address

### organization of this paper

#### Section 2：previous work in branch prediction

#### Section 3：bimodal predictors

#### Section 4：local predictors

#### Section 5：global predictors

#### Section 6：predictors indexed by both global hitory and branch address information

#### Section7：hashing global history and branch addres information before indexing the predictors

#### Section8：the technique for combining multiple predictors

#### Section9：concluding remarks

#### Section10：suggestions for future work

Related Work
------------

#### J.E.Smith：serveral hardware schemes ect. bimoal schenem

#### Lee and A.J.Smith：evaluated several branch prediction scheme

#### McFarling and Hennesy：compared hardware and software approaches

#### Hwu，Conte, Chang：performed a similar study for a wider range of pipeline length

#### Fisher and Freudenberger：studied the stabiliy of profile information

#### Yet and Patt：described both the local and global branch predictor 

#### Pan, So, and Rahmeh：described hwow both global history and branch address information can be used in one predictor

#### Ball ad Larus：described several techniques for guessing the most common branches directions at compile time using static information 

Bimodal Branch Prediton
-----------------------

### background：the behavior of typical branch is order taken or not taken

### simplest approach：a table of counters indexed by the low order address bits in PC

| Q1: use the branch address or the branch instruction address ? |
|----------------------------------------------------------------|


1.  [./image/combining_branch_predictor/image1.png](./image/combining_branch_predictor/image1.png)

#### if taken，counter is incremented and the counter is saturating

#### if not taken, counter is decremented

#### the most significant bit determines the prediction

| Q2: if the counter use to many bits, then it will take a long time to predict the later branch ？ |
|---------------------------------------------------------------------------------------------------|


#### 2-bits long counter can tolerate a branch going an unusual direction one time

#### small table results in degraded prediction accuracy

Reason：multiple branches may share the same counter 

#### alternative implementation：store a tag with each counter and use a set-associative lookup to match

##### disadvantage：if the size of tags is accounted for, a simple array of counters is better

##### if tags were already needed to support branch target buffer, it will not be the case

### quantitative evaluation：use SPEC'89 benchmarks 

| [./image/combining_branch_predictor/image2.png](./image/combining_branch_predictor/image2.png) |
|------------------------------------------|


#### only the first 10 million instructions was simulated

#### Execution traces were obtained n a DECstation 5000 using the pixie tracing facility

#### all counters are initially set as if all previous branches were taken

#### The accuracy increases with predictor size increases

#### the accuracy saturates at 93.5% once each branch maps to a unique counter

#### a set-associative predictor would saturate at the same accuracy

Local Branch Prediction
-----------------------

### backgound：one way to improve on bimodal prediction：recognize that many branches execute repetitive patterns

#### most commom example ：for(i = 1; i \<= 4; i++)

#### execute pattern：(1110)\^n, 1--taken, 0-- not taken, n-- the loop times

| Q3：th loop time is the hole loop or the i \< n |
|-------------------------------------------------|


### A branch prediction uses this pattern --- per-address scheme：named by Yeh and Patt

#### uses two tables

| [./image/combining_branch_predictor/image3.png](./image/combining_branch_predictor/image3.png) |
|------------------------------------------|


##### 1. Hisory table： records the history of recent branches

| Q4: will the entry value of history table change dynamiclly if there is only a loop? |
|--------------------------------------------------------------------------------------|


###### an array indexed by the low-order bits of branch address

###### a set-associative branch history table

###### each ectry records the recent n branches whose branch address is mapped , n--the bits of entry bits

##### 2. Counts table：like the bilodal branch prediction

| Q5：what the point of pattern like (1110) if we use the significant bit of counter to determine branch? |
|---------------------------------------------------------------------------------------------------------|


###### indexed by the branch history stored in the first table

#### local predictor can suffer from two kinds of contention 

##### 1. the branch history may reflect a mix of histories which map to the same entry

###### solution: increase bits of entry

##### 2. one array for counter results in conflict between patterns

### quantitative evaluation：use SPEC'89 benchmarks 

| [./image/combining_branch_predictor/image4.png](./image/combining_branch_predictor/image4.png) |
|------------------------------------------|


#### if the size of predictor is too samll, there will be of no value

#### above 128byte the local predictor is better than bimodal

#### the accuracy approaches 97.1% 

#### less than half as many misspredictions as the bimodal scheme

Global Branch Prediction
------------------------

### background：local branch predictor only considers the current branch

### A scheme：take consideration of other recent branches to make a prediction

#### A single shift register GR：records the direction taken by the most recent n conditional branches

##### [./image/combining_branch_predictor/image5.png](./image/combining_branch_predictor/image5.png)

#### sut for two types of patterns

##### 1st：the direction take by current branch may depend on other recent branches. ect if (x \> 1)... if (x \< 1)...

##### 2nd：by duplicating the behavior of local branch prediction ect for( ){ for( ){ } }

###### [./image/combining_branch_predictor/image6.png](./image/combining_branch_predictor/image6.png)

| Q6: how does the GR change? use the significant bit of GR to judge result? |
|----------------------------------------------------------------------------|


### quantitative evaluation：use SPEC'89 benchmarks 

| for small predictors, the bimodal is better than others，as the size increase, the global is better |
|-----------------------------------------------------------------------------------------------------|


1.  [./image/combining_branch_predictor/image7.png](./image/combining_branch_predictor/image7.png)

#### the information content in each additional address bit decline to zero for increasingly large counter tables.

| Q7: what is the "information coontent"? |
|-----------------------------------------|


##### Reason1：the branch address bits used efficiently distinguish different branches

##### Reason2：As the numbers if counters double, half of branch will share the same counter

##### Reason3：as more counters added, each frequent branch will map to unique counter

#### The information content of GR continue to grow for larger sizes

#####  over 90% of the time each branch goes the same direction which allows a global predictors to identify different branches

##### GR can capture more information than just idnetifying which branch is current

Global Predictor with Index Selection
-------------------------------------

### background：global history information is less efficient at identifying the current branch than using the branch address

### gselect：uses both the branch address and the global history

#### [./image/combining_branch_predictor/image8.png](./image/combining_branch_predictor/image8.png)

### there is a tradeoff betweenusing more history bits or more address bits

### quantitative evaluation

| a gselect predictor have less delay and be easier to pipeline than a local predictor |
|--------------------------------------------------------------------------------------|


1.  [./image/combining_branch_predictor/image9.png](./image/combining_branch_predictor/image9.png)

#### better than simple global prediction or bimodal

#### The storage space required for global history is negligible

#### gselect requires only a single array aceess whereas local prediction requires two array accesses

Global History with Index Sharing
---------------------------------

### backgroud

#### global history information weakly identifies the current branch

#### there is a lot of redundancy in the counter index used by gselect

#### if there are enough address bits to identify the branch, the frequent global history cobinations can be sparse

### gshare: hasing the branch address and the global history

| [./image/combining_branch_predictor/image10.png](./image/combining_branch_predictor/image10.png) |
|--------------------------------------------|


#### hasing it by the exclusive OR of the branch address with the global history

#### gshare is able to separate more cases than gselect

### quantitative evaluation

| [./image/combining_branch_predictor/image11.png](./image/combining_branch_predictor/image11.png) |
|--------------------------------------------|


#### for small predictors, gshare underperform gselect

##### Reason：there is already too much contention for counters between different branches and adding global information just makes if worse

#### for predictor sizes 256 bytes and over, gshare outperforms gselect

Combining Branch predictors
---------------------------

### background

#### the different branch prediction schemes have different advantages

#### the combination can have a better prediction accuracy

### A method: containd two predictors P1 and P2

#### P1 and P2 can be any kind of branch predictor

#### contains an additional counter array to select the best predictors to use

#### use 2-bit up/down saturating counters

##### [./image/combining_branch_predictor/image12.png](./image/combining_branch_predictor/image12.png)

| P1c P2c means if the predictor are correct respectively |
|---------------------------------------------------------|


### quantitative evaluation：use SPEC'89 benchmarks 

| [./image/combining_branch_predictor/image13.png](./image/combining_branch_predictor/image13.png) |
|--------------------------------------------|


#### the combination of bimodal/gshare is useful

#### all the benchmarks were run to completion

#### the predictors array has 1K counters

#### the combination of local/gshare predictor outperforms bimodal/gshare from 2kb size

##### [./image/combining_branch_predictor/image14.png](./image/combining_branch_predictor/image14.png)

#### the accuracy approaches 98.1%

Conclusions
-----------

### this paper presents two new methods for improving branch prediction performance

#### 1st. using the bit-wise exclusive OR of the global branch history and the branch address to access predictor counters

#### 2nd. combining advantages of multiple branch predictors 

##### combined predictors using local and global branch information reach a accuracy of 98.1%

Suggestion for Future Work
--------------------------

#### 1st. parameters like sizes, associativities and the pipeline costs can be explored

#### 2nd. the information such as whether the branch target is forward or backward might be useful

#### 3rt. the sparse branch history might be compressed to reduce the number of counters needed

#### 4th. a compiler with profile support might be able to reduce or eliminate the need for branch predictor

A Appendix
----------

### for section 4, the local prediction. discuss two variations and show that the combined predictor has better performance than these alternatives

#### 1st. indexing the counter array with both the branch address and the local history

##### the number of history bits used to index the counter array is held constant

##### [./image/combining_branch_predictor/image15.png](./image/combining_branch_predictor/image15.png)

| Q8: why I cannot understance these two figures? |
|-------------------------------------------------|


#### 2nd. change the number of history entries

##### using the same number of history entries of history table entires as counters is usually a good choice

###### [./image/combining_branch_predictor/image16.png](./image/combining_branch_predictor/image16.png)
