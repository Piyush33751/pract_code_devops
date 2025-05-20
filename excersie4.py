price_list={'apple' : 1.20, 'orange':1.40, 'watermelon': 6.50, 'pineapple': 2.70, 'pear' : 0.90, 'papaya': 2.95, 'pomegranate': 4.95 }

quantity_list= {'apple': 5, 'orange':5, 'watermelon': 1, 'pineapple': 2, 'pear' : 10, 'papaya': 1, 'pomegranate': 2 }



def total_cost_shopping():
    my_list=[]
    x=0
    for i in price_list:
         my_list.append(price_list[i]*quantity_list[i])
    x=sum(my_list)
    return x

def cost_of_fruits(fruit, quantity):
    for i in price_list:
        if(i==fruit):
            x=price_list[fruit]*quantity
    return x

def main():
    print(cost_of_fruits('apple', 10))
    print(total_cost_shopping())


if __name__ == "__main__":
    main()