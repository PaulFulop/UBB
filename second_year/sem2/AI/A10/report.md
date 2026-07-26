# Simple Report

## 1. Problem description

We have a small Mamdani fuzzy system for a delivery robot.
The goal is to choose a safe speed when the inputs are not exact.
The robot uses three inputs: visibility, obstacle distance, and battery level.
The output is one crisp value: the recommended speed.

## 2. Input and output variables

The input variables are:

- visibility, from 0 to 100 percent;
- obstacle distance, from 0 to 10 meters;
- battery level, from 0 to 100 percent.

The output variable is:

- recommended speed, from 0 to 10 km/h.

I used simple fuzzy sets like low, medium, high, close, far, slow, and fast.
The rules are easy to read and they match common sense.

## 3. Rule base

The rule base combines visibility, obstacle distance, and battery level.
Some examples are:

- if visibility is low or obstacle distance is close, then speed is very slow;
- if visibility is medium and obstacle distance is medium, then speed is slow;
- if visibility is high and obstacle distance is far and battery is high, then speed is fast.

These rules make sense because the robot should slow down when the road is hard to see or when an obstacle is close.

## 4. Mamdani inference mechanism

The system works in five steps:

1. fuzzification: crisp values are turned into membership degrees;
2. rule activation: each rule gets a strength from the input values;
3. implication: the output fuzzy set is clipped by the rule strength;
4. aggregation: all clipped outputs are merged with max;
5. defuzzification: centroid is used to turn the final fuzzy set into one crisp speed.

The result for the example case is smooth, not all-or-nothing.
That is the main advantage over a crisp rule system.
A crisp system changes suddenly when a value crosses a threshold.

## 5. Experiments

The notebook tests several situations.
The robot gives low speed when visibility is poor or the obstacle is close.
It gives higher speed when visibility is good, the obstacle is far, and the battery is high.

For the example case, the output is a medium-low speed, which is reasonable.

## 6. Critical analysis

For the new rule in task 1, the result does not really change.
That happens because another rule already sends the system to the same output set with the same strength.

For task 2, changing the shape of the close obstacle set makes the system more careful around 4 meters.
The speed becomes lower because the robot thinks the obstacle is still somewhat close.

For task 3, the crisp system is easier to write, but the fuzzy one behaves better when the inputs are a little uncertain.
That is why the fuzzy system fits this problem better.

## 7. Possible improvements

The system could be improved by tuning the membership functions more carefully.
It could also use extra inputs like road condition or weather.
Another improvement would be to add more rules and test them on more cases.

## Discussion questions

1. Why is a fuzzy rule-based system useful in uncertain environments?

It is useful because it can work with vague or noisy inputs instead of strict thresholds.

2. What is the role of membership functions?

Membership functions turn a crisp value into a degree of belonging to a fuzzy set.

3. What does it mean for a rule to be partially activated?

It means the rule is not fully true or fully false, so it contributes only partly to the final result.

4. Why does Mamdani inference need an aggregation step?

Aggregation is needed to combine the conclusions of all rules into one final fuzzy output.

5. Why is defuzzification necessary?

Defuzzification is needed because the system must give one final crisp speed, not only a fuzzy set.

6. What are the limitations of this system?

The system depends on hand-made rules and hand-made membership functions, so it can be hard to tune well.

7. How could this system be validated in a real robotic application?

It could be validated by testing it on real robot data and comparing the chosen speed with safe human or expert decisions.

In short, the system works well for small uncertain decisions.
It is simple, readable, and the final speed changes smoothly.
