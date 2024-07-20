//
// Created by yusse on 20/07/2024.
//
#include "TaskManager.h"
TaskManager::TaskManager():employees_num(0),task_index(0),employees(new Person[MAX_PERSONS]){}

TaskManager::~TaskManager() {
    delete[] employees;
}

void TaskManager::assignTask(const std::string &personName, const Task &task){
    Task newTask(task.getPriority(),task.getType(),task.getDescription());
    newTask.setId(task_index);
    task_index++;
    bool done= false;
    for(int i=0;i<employees_num;i++){
        if(employees[i].getName() == personName){
            employees[i].assignTask(newTask);
            All_Tasks.insert(newTask);
            done = true;
        }
    }
    if(!done){
        if(employees_num < 10){
            Person newPerson(personName);
            newPerson.assignTask(newTask);
            employees[employees_num]=newPerson;
            employees_num++;
            All_Tasks.insert(newTask);
        } else{
            throw std::runtime_error("runtime_error");
        }
    }

}

void TaskManager::completeTask(const std::string &personName) {
    for(int i=0;i<employees_num;i++){
        if(employees[i].getName() == personName){
           int id= employees[i].completeTask();
            for(SortedList<Task>::ConstIterator it = All_Tasks.begin(); it != All_Tasks.end();++it){
                if((*it).getId() == id){
                    All_Tasks.remove(it);
                }
            }
        }
    }
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    for(int i=0;i<employees_num;i++){
        SortedList<Task> temp=employees[i].getTasks();
        for(SortedList<Task>::ConstIterator it = temp.begin(); it != temp.end();++it){
            if((*it).getType() == type){
                Task newTask((*it).getPriority() + priority, (*it).getType(), (*it).getDescription());
                newTask.setId((*it).getId());
                temp.remove(it);
                temp.insert(newTask);
            }
        }
    }
    for(SortedList<Task>::ConstIterator it = All_Tasks.begin(); it != All_Tasks.end();++it){
        if((*it).getType() == type){
            Task newTask((*it).getPriority() + priority, (*it).getType(), (*it).getDescription());
            newTask.setId((*it).getId());
            All_Tasks.remove(it);
            All_Tasks.insert(newTask);
        }
    }
//    SortedList<Task> filterList = All_Tasks.filter([type](const Task &task) { return task.getType() == type; });
//    SortedList<Task> newList;
//    for (const Task &task: filterList) {
//        Task newTask(task.getPriority() + priority, task.getType(), task.getDescription());
//        newTask.setId(task.getId());
//        newList.insert(newTask);
//    }
//    for (const Task &task: newList) {
//        All_Tasks.insert(task);
//    }
}

void TaskManager::printAllEmployees() const {
    for(int i=0;i<employees_num;i++){
        std::cout << employees[i] << std::endl;
    }
}

void TaskManager::printAllTasks() const {
    for(const Task& task : All_Tasks){
        std::cout << task << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    for(const Task& task : All_Tasks){
        if(task.getType()==type){
            std::cout << task << std::endl;
        }
    }
}