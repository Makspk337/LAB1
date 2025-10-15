package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "strings"
)

type Entry struct {
    typeName string
    ptr      interface{}
    name     string
}

var entries []Entry
var entryCount int

func init() {
    entries = make([]Entry, 100)
    entryCount = 0
}

func findEntry(name string) *Entry {
    for i := 0; i < entryCount; i++ {
        if entries[i].name == name {
            return &entries[i]
        }
    }
    return nil
}

func saveToFile(filename string) {
    file, err := os.Create(filename)
    if err != nil {
        return
    }
    defer file.Close()

    for i := 0; i < entryCount; i++ {
        e := entries[i]
        switch e.typeName {
        case "ARRAY":
            arr := e.ptr.(*Array)
            fmt.Fprintf(file, "ARRAY %s %s\n", arr.name, arr.read())
        case "FLIST":
            list := e.ptr.(*ForwardList)
            fmt.Fprintf(file, "FLIST %s %s\n", list.name, list.read())
        case "DLIST":
            list := e.ptr.(*DoublyList)
            fmt.Fprintf(file, "DLIST %s %s\n", list.name, list.read())
        case "STACK":
            stack := e.ptr.(*Stack)
            fmt.Fprintf(file, "STACK %s %s\n", stack.name, stack.read())
        case "QUEUE":
            queue := e.ptr.(*Queue)
            fmt.Fprintf(file, "QUEUE %s %s\n", queue.name, queue.read())
        case "TREE":
            // tree := e.ptr.(*Tree)
            // fmt.Fprintf(file, "TREE %s %s\n", tree.name, tree.read())
            // TODO: реализовать дерево
        }
    }
}

func loadFromFile(filename string) {
    file, err := os.Open(filename)
    if err != nil {
        return
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        line := scanner.Text()
        parts := strings.Fields(line)
        if len(parts) < 2 {
            continue
        }

        typeName := parts[0]
        name := parts[1]
        values := parts[2:]

        switch typeName {
        case "ARRAY":
            arr := createArray(name)
            for _, val := range values {
                arr.pushBack(val)
            }
            entries[entryCount] = Entry{"ARRAY", arr, name}
            entryCount++
        case "FLIST":
            list := createForwardList(name)
            for _, val := range values {
                list.pushTail(val)
            }
            entries[entryCount] = Entry{"FLIST", list, name}
            entryCount++
        case "DLIST":
            list := createDoublyList(name)
            for _, val := range values {
                list.pushTail(val)
            }
            entries[entryCount] = Entry{"DLIST", list, name}
            entryCount++
        case "STACK":
            stack := createStack(name)
            for _, val := range values {
                stack.push(val)
            }
            entries[entryCount] = Entry{"STACK", stack, name}
            entryCount++
        case "QUEUE":
            queue := createQueue(name)
            for _, val := range values {
                queue.push(val)
            }
            entries[entryCount] = Entry{"QUEUE", queue, name}
            entryCount++
        case "TREE":
            // TODO: реализовать загрузку дерева
        }
    }
}

func main() {
    if len(os.Args) < 5 {
        return
    }

    var filename, query string
    for i := 1; i < len(os.Args); i++ {
        arg := os.Args[i]
        if arg == "--file" && i+1 < len(os.Args) {
            filename = os.Args[i+1]
            i++
        } else if arg == "--query" && i+1 < len(os.Args) {
            query = os.Args[i+1]
            i++
        }
    }

    if filename == "" || query == "" {
        return
    }

    loadFromFile(filename)

    parts := strings.Fields(query)
    if len(parts) == 0 {
        return
    }

    cmd := parts[0]
    args := parts[1:]

    switch cmd {
    case "MPUSH":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e == nil {
                arr := createArray(name)
                arr.pushBack(val)
                entries[entryCount] = Entry{"ARRAY", arr, name}
                entryCount++
            } else {
                arr := e.ptr.(*Array)
                arr.pushBack(val)
            }
        }

    case "MSET":
        if len(args) >= 3 {
            name, indexStr, val := args[0], args[1], args[2]
            index, err := strconv.Atoi(indexStr)
            if err == nil {
                e := findEntry(name)
                if e != nil {
                    arr := e.ptr.(*Array)
                    arr.insert(index, val)
                }
            }
        }

    case "MREPLACE":
        if len(args) >= 3 {
            name, indexStr, val := args[0], args[1], args[2]
            index, err := strconv.Atoi(indexStr)
            if err == nil {
                e := findEntry(name)
                if e != nil {
                    arr := e.ptr.(*Array)
                    arr.replace(index, val)
                }
            }
        }

    case "MGET":
        if len(args) >= 2 {
            name, indexStr := args[0], args[1]
            index, err := strconv.Atoi(indexStr)
            if err == nil {
                e := findEntry(name)
                if e != nil {
                    arr := e.ptr.(*Array)
                    fmt.Println(arr.get(index))
                }
            }
        }

    case "MDEL":
        if len(args) >= 2 {
            name, indexStr := args[0], args[1]
            index, err := strconv.Atoi(indexStr)
            if err == nil {
                e := findEntry(name)
                if e != nil {
                    arr := e.ptr.(*Array)
                    arr.delete(index)
                }
            }
        }

    case "MLEN":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                arr := e.ptr.(*Array)
                fmt.Println(arr.length())
            }
        }

    case "FPUSH_HEAD":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e == nil {
                list := createForwardList(name)
                list.pushHead(val)
                entries[entryCount] = Entry{"FLIST", list, name}
                entryCount++
            } else {
                list := e.ptr.(*ForwardList)
                list.pushHead(val)
            }
        }

    case "FPUSH_TAIL":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e == nil {
                list := createForwardList(name)
                list.pushTail(val)
                entries[entryCount] = Entry{"FLIST", list, name}
                entryCount++
            } else {
                list := e.ptr.(*ForwardList)
                list.pushTail(val)
            }
        }

    case "FPUSH_BEFORE":
        if len(args) >= 3 {
            name, target, val := args[0], args[1], args[2]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                list.pushBefore(target, val)
            }
        }

    case "FPUSH_AFTER":
        if len(args) >= 3 {
            name, target, val := args[0], args[1], args[2]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                list.pushAfter(target, val)
            }
        }

    case "FDEL_HEAD":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                list.deleteHead()
            }
        }

    case "FDEL_TAIL":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                list.deleteTail()
            }
        }

    case "FDEL_BEFORE":
        if len(args) >= 2 {
            name, target := args[0], args[1]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                list.deleteBefore(target)
            }
        }

    case "FDEL_AFTER":
        if len(args) >= 2 {
            name, target := args[0], args[1]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                list.deleteAfter(target)
            }
        }

    case "FDEL_VALUE":
        if len(args) >= 2 {
            name, target := args[0], args[1]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                list.deleteValue(target)
            }
        }

    case "FFIND":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                if list.find(val) {
                    fmt.Println("TRUE")
                } else {
                    fmt.Println("FALSE")
                }
            } else {
                fmt.Println("FALSE")
            }
        }

    case "FGET":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                fmt.Println(list.read())
            }
        }

    case "FGETR":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*ForwardList)
                fmt.Println(list.readReverse())
            }
        }

    case "LPUSH_HEAD":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e == nil {
                list := createDoublyList(name)
                list.pushHead(val)
                entries[entryCount] = Entry{"DLIST", list, name}
                entryCount++
            } else {
                list := e.ptr.(*DoublyList)
                list.pushHead(val)
            }
        }

    case "LPUSH_TAIL":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e == nil {
                list := createDoublyList(name)
                list.pushTail(val)
                entries[entryCount] = Entry{"DLIST", list, name}
                entryCount++
            } else {
                list := e.ptr.(*DoublyList)
                list.pushTail(val)
            }
        }

    case "LDEL_HEAD":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*DoublyList)
                list.deleteHead()
            }
        }

    case "LDEL_TAIL":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*DoublyList)
                list.deleteTail()
            }
        }

    case "LDEL_VALUE":
        if len(args) >= 2 {
            name, target := args[0], args[1]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*DoublyList)
                list.deleteValue(target)
            }
        }

    case "LFIND":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*DoublyList)
                if list.find(val) {
                    fmt.Println("TRUE")
                } else {
                    fmt.Println("FALSE")
                }
            } else {
                fmt.Println("FALSE")
            }
        }

    case "LGET":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*DoublyList)
                fmt.Println(list.read())
            }
        }

    case "LGETR":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                list := e.ptr.(*DoublyList)
                fmt.Println(list.readReverse())
            }
        }

    case "SPUSH":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e == nil {
                stack := createStack(name)
                stack.push(val)
                entries[entryCount] = Entry{"STACK", stack, name}
                entryCount++
            } else {
                stack := e.ptr.(*Stack)
                stack.push(val)
            }
        }

    case "SPOP":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                stack := e.ptr.(*Stack)
                fmt.Println(stack.pop())
            }
        }

    case "SPEEK":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                stack := e.ptr.(*Stack)
                fmt.Println(stack.peek())
            }
        }

    case "QPUSH":
        if len(args) >= 2 {
            name, val := args[0], args[1]
            e := findEntry(name)
            if e == nil {
                queue := createQueue(name)
                queue.push(val)
                entries[entryCount] = Entry{"QUEUE", queue, name}
                entryCount++
            } else {
                queue := e.ptr.(*Queue)
                queue.push(val)
            }
        }

    case "QPOP":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                queue := e.ptr.(*Queue)
                fmt.Println(queue.pop())
            }
        }

    case "QPEEK":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                queue := e.ptr.(*Queue)
                fmt.Println(queue.peek())
            }
        }

    case "PRINT":
        if len(args) >= 1 {
            name := args[0]
            e := findEntry(name)
            if e != nil {
                switch e.typeName {
                case "ARRAY":
                    arr := e.ptr.(*Array)
                    fmt.Println(arr.read())
                case "FLIST":
                    list := e.ptr.(*ForwardList)
                    fmt.Println(list.read())
                case "DLIST":
                    list := e.ptr.(*DoublyList)
                    fmt.Println(list.read())
                case "STACK":
                    stack := e.ptr.(*Stack)
                    fmt.Println(stack.read())
                case "QUEUE":
                    queue := e.ptr.(*Queue)
                    fmt.Println(queue.read())
                    // case "TREE":
                    //     tree := e.ptr.(*Tree)
                    //     fmt.Println(tree.read())
                }
            }
        }
    }

    saveToFile(filename)
}
