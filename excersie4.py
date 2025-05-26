price_list={'apple' : 1.20, 'orange':1.40, 'watermelon': 6.50, 'pineapple': 2.70, 'pear' : 0.90, 'papaya': 2.95, 'pomegranate': 4.95 }

quantity_list= {'apple': 5, 'orange':5, 'watermelon': 1, 'pineapple': 2, 'pear' : 10, 'papaya': 1, 'pomegranate': 2 }



def total_cost_shopping():
    my_list=[]
    cost=0
    x=0
    for i in price_list:
        cost=price_list[i]*quantity_list[i]
        my_list.append(cost)
    x=sum(my_list)    
    return x
def cost_of_fruits(fruit, quantity):
    x=price_list[fruit] * quantity
    return x 
 
def whatever_want(x,y):
    x=input("Put the name of the fruit you want") 
    y=int(input("put the nummber of fruits you want"))
    z=print(cost_of_fruits(x, y))
def main():
    print(cost_of_fruits('apple', 10))
    print(total_cost_shopping())
    # print(whatever_want())
    print(price_list.get("apple"))


if __name__ == "__main__":
    main()