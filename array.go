package main

type Array struct {
    name     string
    data     []string
    size     int
    capacity int
}

func createArray(name string) *Array {
    return &Array{
        name:     name,
        data:     make([]string, 4),
        size:     0,
        capacity: 4,
    }
}

func (arr *Array) pushBack(value string) {
    if arr.size >= arr.capacity {
        arr.capacity *= 2
        newData := make([]string, arr.capacity)
        copy(newData, arr.data)
        arr.data = newData
    }
    arr.data[arr.size] = value
    arr.size++
}

func (arr *Array) insert(index int, value string) {
    if index < 0 || index > arr.size {
        return
    }
    if arr.size >= arr.capacity {
        arr.capacity *= 2
        newData := make([]string, arr.capacity)
        copy(newData, arr.data)
        arr.data = newData
    }
    for i := arr.size; i > index; i-- {
        arr.data[i] = arr.data[i-1]
    }
    arr.data[index] = value
    arr.size++
}

func (arr *Array) get(index int) string {
    if index < 0 || index >= arr.size {
        return ""
    }
    return arr.data[index]
}

func (arr *Array) delete(index int) {
    if index < 0 || index >= arr.size {
        return
    }
    for i := index; i < arr.size-1; i++ {
        arr.data[i] = arr.data[i+1]
    }
    arr.size--
}

func (arr *Array) replace(index int, value string) {
    if index < 0 || index >= arr.size {
        return
    }
    arr.data[index] = value
}

func (arr *Array) length() int {
    return arr.size
}

func (arr *Array) read() string {
    if arr.size == 0 {
        return ""
    }
    result := ""
    for i := 0; i < arr.size; i++ {
        result += arr.data[i]
        if i != arr.size-1 {
            result += " "
        }
    }
    return result
}
