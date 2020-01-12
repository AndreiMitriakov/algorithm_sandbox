fn partitions(n: i32) -> i32 {
    let mut a: Vec<i32> = vec![0; (n + 1) as usize];
    let mut k: usize = 1;
    let mut l: usize;
    let mut x: i32;
    let mut y: i32 = n - 1;
    let mut cnt: i32 = 0;
    while k != 0 {
        x = a[k - 1] + 1;
        k -= 1;
        while 2 * x <= y {
            a[k] = x;
            y -= x;
            k += 1;
        }
        l = k + 1;
        while x <= y {
            a[k] = x;
            a[l] = y;
            cnt += 1;
            x += 1;
            y -= 1;
        }
        a[k] = x + y;
        y = x + y - 1;
        cnt += 1;
    }
    return cnt;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic_test_01() {
        assert_eq!(partitions(1), 1);
    }

    #[test]
    fn basic_test_05() {
        assert_eq!(partitions(5), 7);
    }

    #[test]
    fn basic_test_10() {
        assert_eq!(partitions(10), 42);
    }

    #[test]
    fn basic_test_25() {
        assert_eq!(partitions(25), 1958);
    }
}

fn main() {
    let c: i32 = partitions(5);
    println!("Result {}", c);
}
