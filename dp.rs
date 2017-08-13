#![feature(test)]

extern crate test;

struct MinDist<'a> {
    pred: isize,
    curr: isize,
    word1: &'a str,
    word2: &'a str,
    line: Vec<isize>,
    grid: Vec<isize>
}

impl<'a> MinDist<'a> {
    pub fn new(word1: &'a str, word2: &'a str) -> MinDist<'a> {
        let line = {
            let mut v = Vec::with_capacity(word1.len() + 1);
            for i in 0..word1.len()+1 {
                v.push(i as isize);
            }
            v
        };

        let grid = {
            let n = word1.len()+1;
            let m = word2.len()+1;
            let mut grid = vec![0isize; n*m];
            for i in 0..n {grid[0*n + i] = i as isize; }
            for i in 0..m {grid[i*n + 0] = i as isize; }
            grid
        };

        MinDist {
            pred: 0,
            curr: 0,
            word1: word1,
            word2: word2,
            line: line,
            grid: grid
        }
    }

    pub fn min_distance(&mut self) -> isize {
        self._min_dist(self.word1.as_bytes(), self.word2.as_bytes())

    }

    fn _min_dist2(&mut self, s: &[u8], t: &[u8]) -> isize {
        if s.len() == 0 || t.len() == 0 {
            return std::cmp::max(s.len(), t.len()) as isize;
        }


        let (n, m) = (s.len()+1, t.len()+1);
        #[cfg(debug)]
        for l in self.grid.chunks(n) { println!("{:?}", l); }

        for r in 0..m-1 {
            for c in 0..n-1 {
                self.grid[(r+1)*n + c+1] = match t[r] == s[c] {
                    true => self.grid[r*n + c],
                    _ => {
                        [self.grid[r*n + c],
                        self.grid[(r+1)*n + c],
                        self.grid[r*n + c + 1]].iter().min().unwrap() + 1
                    }
                };
            }
        }
        #[cfg(debug)]
        for l in self.grid.chunks(n) { println!("{:?}", l); }

        self.grid[self.grid.len()-1]
    }

    fn _min_dist(&mut self, s: &[u8], t: &[u8]) -> isize {
        if s.len() == 0 || t.len() == 0 {
            return std::cmp::max(s.len(), t.len()) as isize;
        }

        for i in 0..t.len() {
            self.line[0] = i as isize;
            self.pred = i as isize+1;
            for j in 0..s.len() {
                self.curr = match t[i] == s[j] {
                    true => self.line[j],
                    _ => [self.line[j], self.pred, self.line[j+1]].iter().min().unwrap() + 1
                };
                self.line[j] = self.pred;
                self.pred = self.curr;
            }
            self.line[s.len()] = self.pred;
        }
        println!("{:?}", self.line);

        self.curr
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_min_dist() {

        fn do_test(s: &str, t: &str, expect: isize) {
            let mut md = MinDist::new(s, t); 
            let v = md.min_distance();
            println!("{}, {} = {}", s, t, v);
            assert_eq!(v, expect);
        }

        do_test("", "", 0); // 0    
        do_test("zoologicoarchaeologist", "zoogeologist", 10); // 10
        do_test("plasma", "altruism", 6); // 6
        do_test("", "help", 4); // 4
        do_test("a", "ba", 1); // 1
        do_test("a", "bl", 2); // 2
        do_test("gumbo", "gambol", 2); // 2
        do_test("hello", "hallo", 1); // 1
        do_test("hello", "hllo", 1); // 1
    }
}
