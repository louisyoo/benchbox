/* //////////////////////////////////////////////////////////////////////////////////////
 * imports
 */
package main
import (
    "fmt"
    "runtime"
    "time"
    )

/* //////////////////////////////////////////////////////////////////////////////////////
 * globals
 */
const COUNT = 10000000

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementaiton
 */
func channeltask(channel <-chan int){

    for {

        <- channel
    }
}

/* //////////////////////////////////////////////////////////////////////////////////////
 * main
 */
func main(){

    // single cpu
    runtime.GOMAXPROCS(1)

    // make channel
    channel := make(chan int, 0)

    // init duration
    duration := time.Now().UnixNano()

    // create coroutine task
    go channeltask(channel)

    // in main goroutine
    count := COUNT
    for {

        count--
        channel <- count
        if count == 0 {
            break
        }
    }

    // computing time
    duration = (time.Now().UnixNano() - duration) / 1000000

    // trace
    fmt.Printf("channel: go: %d passes in %d ms, %d passes per second\n", COUNT, duration, (1000 * COUNT) / duration)
}
