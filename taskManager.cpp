#include <iostream>
#include <string>
#include <iomanip>

using namespace std;


// Resource structure
struct Resource {
    int id;
    string name;
    string type;
    float efficiency;
    Resource* next;

    Resource(int id, const string& name, const string& type, float efficiency)
        : id(id), name(name), type(type), efficiency(efficiency), next(nullptr) {}
};

// Task structure
struct Task {
    int id;
    string name;
    float duration;
    float startTime;
    float endTime;
    Resource* resource;
    Task* dependencies[2]; 
    Task* next; 
    bool processed; 

    Task(int id, const string& name, float duration, Resource* resource)
        : id(id), name(name), duration(duration), startTime(0), endTime(0), resource(resource), next(nullptr), processed(false) {
        dependencies[0] = dependencies[1] = nullptr;
    }
};


void addResource(Resource* r, Resource*& head) {  //function to add resources to the linked list
    if (!head) {
        head = r;
        return;
    }
    Resource* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = r;
}


Task* addTask(Task* t, Task*& head) {  //function to add tasks to the linked list
    if (!head) {
        head = t;
        return head;
    }
    Task* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = t;
    return head;
}


void addDependency(Task* task, Task* dependency) {  //function to add dependencies to the tasks
    for (int i = 0; i < 2; ++i) {
        if (!task->dependencies[i]) {
            task->dependencies[i] = dependency;
            break;
        }
    }
}


bool canProcessTask(Task* task) {  //function to check if the task can be processed
    for (int i = 0; i < 2; ++i) {
        if (task->dependencies[i] && !task->dependencies[i]->processed) {
            return false; 
        }
    }
    return true;
}

void calculateTaskTimes(Task* head) {  //function to calculate the start and end times of the tasks
    Task* temp = head;
    float resourceEndTimes[10] = {0};  

    
    temp = head;
    while (temp) {
        if (!temp->dependencies[0] && !temp->dependencies[1]) {
            
            float resourceEndTime = (temp->resource) ? resourceEndTimes[temp->resource->id] : 0;

            
            temp->startTime = resourceEndTime;

            if (temp->resource) {
                temp->endTime = temp->startTime + (temp->duration / temp->resource->efficiency);
                resourceEndTimes[temp->resource->id] = temp->endTime;
            } else {

                temp->endTime = temp->startTime + temp->duration;
            }

            temp->processed = true;
        }
        temp = temp->next;
    }

    
    bool allProcessed = false;

    while (!allProcessed) {
        allProcessed = true;

        temp = head; 

        while (temp) {
            if (!temp->processed && canProcessTask(temp)) {  
                float maxDependencyEndTime = 0;

                
                for (int i = 0; i < 2; ++i) {
                    if (temp->dependencies[i] && temp->dependencies[i]->endTime > maxDependencyEndTime) {
                        maxDependencyEndTime = temp->dependencies[i]->endTime;
                    }
                }

                
                float resourceEndTime = (temp->resource) ? resourceEndTimes[temp->resource->id] : 0;
                temp->startTime = max(maxDependencyEndTime, resourceEndTime);

                
                if (temp->resource) {
                    temp->endTime = temp->startTime + (temp->duration / temp->resource->efficiency);
                    resourceEndTimes[temp->resource->id] = temp->endTime;
                } else {
                    
                    temp->endTime = temp->startTime + temp->duration;
                }

                
                temp->processed = true;

                allProcessed = false; 
            }
            temp = temp->next;
        }

        if (allProcessed) {
            break;
        }
    }
}


void printTasks(Task* head) {  //function to print the tasks
    cout << left << setw(5) << "Id" << setw(10) << "Name" << setw(10) << "Duration" << setw(20) << "Dependencies" << setw(10) << "Resource" << setw(12) << "Start Time" << setw(10) << "End Time" << endl;

    Task* temp = head;
    while (temp) {
        cout << left << setw(5) << temp->id << setw(10) << temp->name << setw(10) << temp->duration;
        
        
        string depStr = "";
        if (temp->dependencies[0]) {
            depStr += temp->dependencies[0]->name;
        }
        if (temp->dependencies[1]) {
            if (!depStr.empty()) depStr += ", ";
            depStr += temp->dependencies[1]->name;
        }
        cout << setw(20) << depStr;

        
        if (temp->resource) {
            cout << setw(10) << temp->resource->name;
        } else {
            cout << setw(10) << "";
        }

        cout << setw(12) << fixed << setprecision(1) << temp->startTime << setw(10) << temp->endTime << endl;

        temp = temp->next;
    }
}

Task* findTaskById(Task* head, int id) {  //function to find the task by id
    Task* temp = head;
    while (temp) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}


bool hasCyclicDependency(Task* task, bool visited[], bool stack[]) {  //function to check if there is a cyclic dependency
    if (stack[task->id]) return true; 
    if (visited[task->id]) return false; 

    visited[task->id] = true;
    stack[task->id] = true;

    for (int i = 0; i < 2; ++i) {
        if (task->dependencies[i]) {
            if (hasCyclicDependency(task->dependencies[i], visited, stack)) {
                return true;
            }
        }
    }

    stack[task->id] = false;
    return false;
}








int main() {
    
    Resource* r1 = new Resource(1, "A", "Type 1", 2.0);
    Resource* r2 = new Resource(2, "B", "Type 2", 0.5);

    
    Task* t1 = new Task(1, "A", 5, r1);   
    Task* t2 = new Task(2, "B", 10, r1);  
    Task* t3 = new Task(3, "C", 15, r2);  
    Task* t4 = new Task(4, "D", 10, r1);  
    Task* t5 = new Task(5, "E", 5, r1);  


    
    addDependency(t1, t2);  
    addDependency(t2, t3);  
    addDependency(t2, t4);  
    addDependency(t4, t5); 


    Task* head = nullptr;
    addTask(t1, head);
    addTask(t2, head);
    addTask(t3, head);
    addTask(t4, head);
    addTask(t5, head);

    
    calculateTaskTimes(head);

    
    printTasks(head);

    return 0;
} 




// int main() {
//     // Create fixed resources
//     Resource* r1 = new Resource(1, "A", "Type 1", 2.0);
//     Resource* r2 = new Resource(2, "B", "Type 2", 0.5);

//     Task* head = nullptr;
//     int choice;
//     int taskId = 1;

//     while (true) {
//         // Display the menu
//         cout << "\nMenu:\n";
//         cout << "1. Add Task\n";
//         cout << "2. Add Dependency\n";
//         cout << "3. Process Tasks\n";
//         cout << "4. Display Tasks\n";
//         cout << "5. Exit\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         if (choice == 1) {
//             string taskName;
//             float duration;
//             int resourceChoice;

//             cout << "Enter task name: ";
//             cin >> taskName;
//             cout << "Enter task duration: ";
//             cin >> duration;
//             cout << "Select resource (1 for A, 2 for B, 0 for None): ";
//             cin >> resourceChoice;

//             Resource* selectedResource = nullptr;
//             if (resourceChoice == 1) {
//                 selectedResource = r1;
//             } else if (resourceChoice == 2) {
//                 selectedResource = r2;
//             }

//             // Check for duplicate task ID
//             if (findTaskById(head, taskId)) {
//                 cout << "Task with ID " << taskId << " already exists. Please use a different ID.\n";
//                 continue;
//             }

//             // Create the task
//             Task* newTask = new Task(taskId++, taskName, duration, selectedResource);
//             head = addTask(newTask, head);
//             cout << "Task added successfully.\n";

//         } else if (choice == 2) {
//             int taskId1, taskId2;
//             cout << "Enter dependent task ID: ";
//             cin >> taskId1;
//             cout << "Enter dependency task ID: ";
//             cin >> taskId2;

//             Task* task1 = findTaskById(head, taskId1);
//             Task* task2 = findTaskById(head, taskId2);

//             if (!task1 || !task2) {
//                 cout << "One or both task IDs are invalid.\n";
//                 continue;
//             }

//             // Check for cyclic dependency
//             bool visited[100] = {false}; // Assuming max 100 tasks
//             bool stack[100] = {false};   // Assuming max 100 tasks

//             if (hasCyclicDependency(task2, visited, stack)) {
//                 cout << "Error: Adding this dependency would create a cycle.\n";
//                 continue;
//             }

//             addDependency(task1, task2);
//             cout << "Dependency added successfully.\n";

//         } else if (choice == 3) {
//             calculateTaskTimes(head);
//             cout << "Tasks processed successfully.\n";

//         } else if (choice == 4) {
//             printTasks(head);

//         } else if (choice == 5) {
//             // Exit the program
//             break;

//         } else {
//             cout << "Invalid choice. Please try again.\n";
//         }
//     }

//     // Cleanup dynamically allocated memory (omitted for brevity)

//     return 0;
// }
