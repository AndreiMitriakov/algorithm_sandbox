fn prime_factors(n: i64) -> String {
    let mut res: String = String::new();
    let mut v: Vec<usize> = Vec::new();
    let mut d: Vec<usize> = Vec::new();
    let mut c: f64;
    let mut j: usize;
    for i in 2..n as usize{
        v.push(i);
    }
    for i in 0..v.len() {
        if v[i] != 0 {
            if (n as f64) % (v[i] as f64) == 0.0 {
                j = v[i].clone();
                v = v.iter().map(|x| 
                {
                    if (*x as f32 % j as f32 == 0_f32) && x > &j 
                        {0_usize}
                    else 
                        {*x} 
                }).collect::<Vec<usize>>();
            }
            else {
                v[i] = 0;
            }
        }
    }
    v = v.iter().filter(|&&x| x != 0).map(|&x| x).collect();
    
    for elem in v.clone() {
        c = n as f64;
        j = 0;
        loop {
            if c % elem as f64 == 0.0 {
                c /= elem as f64;
                j += 1;
            }
            else {
                d.push(j);
                break;
            }
        }
    }
    //  "(2**2)(3**3)(5)(7)(11**2)(17)"
    for i in 0..v.len() {
        if d[i] == 1 {
            res = res + &format!("({})", v[i]);                
        }
        else {
            res = res + &format!("({}**{})", v[i], d[i]);    
        }
    }
    res
}

fn main() {
println!("{}", prime_factors(7775460));
}
