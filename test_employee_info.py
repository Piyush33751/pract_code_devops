import excer as e_i

employee_data = [
    {"name": "John", "age": 30, "department": "Sales", "salary": 50000},
    {"name": "Jane", "age": 25, "department": "Marketing", "salary": 60000},
    {"name": "Mary", "age": 23, "department": "Marketing", "salary": 56000},
    {"name": "Chloe",  "age": 35, "department": "Engineering", "salary": 70000},
    {"name": "Mike", "age": 32, "department": "Engineering", "salary": 65000},
    {"name": "Peter", "age": 40, "department": "Sales", "salary": 60000}
]


def test_calculate_average_salary():
    x=50000 +60000+56000+70000+65000+60000
    avg=(x/6)
    y=e_i.calculate_average_salary()
    assert(avg==y)

def test_get_employees_by_age_range():
    mying_listing=[]
    for i in employee_data:
        if(i["age"]>22 and i["age"]<33):
            mying_listing.append(i)
    y=e_i. get_employees_by_age_range(22, 33)
    assert(mying_listing==y)

def test_get_employees_by_dept():
    myingir_list=[]
    for i in employee_data:
        if(i["department"]=="Sales"):
            myingir_list.append(i)
    
    y=e_i. get_employees_by_dept("Sales")
    assert(y== myingir_list)
    
def test_searcher():
    int_my_lit=[]
    for i in employee_data:
        if i["name"][0]=="J":
            int_my_lit.append(i)
    y=e_i.find_specific_names("J")
    assert(y==int_my_lit)