#![feature(test)]

extern crate test;
//use std::collections::Vec;

#[derive(Debug, Clone)]
pub struct TreeNode {
    val: isize,
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>
}

impl TreeNode {
    pub fn single(val: isize) -> TreeNode {
        TreeNode {
            val: val, left: None, right: None
        }
    }

    pub fn full(val: isize, left: TreeNode, right: TreeNode) -> TreeNode {
        TreeNode {
            val: val, left: Some(Box::new(left)), right: Some(Box::new(right))
        }
    }

    pub fn left(val: isize, left: TreeNode) -> TreeNode {
        let right = None;
        let left = Some(Box::new(left));
        TreeNode {
            val, left, right
        }
    }

    pub fn right(val: isize, right: TreeNode) -> TreeNode {
        let left = None;
        let right = Some(Box::new(right));
        TreeNode {
            val, left, right
        }
    }
}

pub fn inorder_traversal(root: &TreeNode) -> &[isize] {
    let mut res = Vec::new();

    fn it(root: &TreeNode, res: &mut Vec<isize>) {
        if root.left.is_some() { it(root.left.as_ref().unwrap(), res); }
        res.push(root.val);
        if root.right.is_some() { it(root.right.as_ref().unwrap(), res); }
    }


    it(root, &mut res);
    unsafe { &*Box::into_raw(res.into_boxed_slice()) }
}

struct MaxPathSum {
    max: isize,
}

impl MaxPathSum {
    pub fn new() -> MaxPathSum {
        MaxPathSum { max: 0 }
    }

    pub fn max_path_sum(&mut self, root: &TreeNode) -> isize {
        let l = match root.left {
            Some(ref v) => self.max_path_sum(v),
            None => 0
        };

        let r = match root.right {
            Some(ref v) => self.max_path_sum(v),
            None => 0
        };

        if self.max < l + r + root.val {
            self.max = l + r + root.val;
        }

        std::cmp::max(l + root.val, r + root.val)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_normal() {
        {
            let r = TreeNode {
                val: 1, 
                left: None,
                right: Some(Box::new(TreeNode {
                    val: 2,
                    left: Some(Box::new(TreeNode {val: 3, left: None, right: None})),
                    right: None
                }))
            };

            let v = inorder_traversal(&r);
            println!("{:?}", v);
            unsafe { Box::from_raw(v.as_ptr() as *mut isize) };
        }

        {
            let r = TreeNode {
                val: 1, 
                left: Some(Box::new(TreeNode {
                    val: 4,
                    left: Some(Box::new(TreeNode {val: 2, left: None, right: None})),
                    right: None
                })),
                right: Some(Box::new(TreeNode {val: 3, left: None, right: None}))
            };

            let v = inorder_traversal(&r);
            println!("{:?}", v);
            unsafe { Box::from_raw(v.as_ptr() as *mut isize) };
        }
    }

    #[test]
    fn test_max_path_sum() {
        let mut res = MaxPathSum::new();

        {
            res.max = 0;
            let r = TreeNode::full(
                1,
                TreeNode::full(
                    4,
                    TreeNode::single(2),
                    TreeNode::single(7)),
                TreeNode::single(3));

            res.max_path_sum(&r);
            println!("{}", res.max);
            assert_eq!(res.max, 15);
        }

        {
            res.max = 0;
            let r = TreeNode::full(
                1,
                TreeNode::left(
                    4,
                    TreeNode::right(2, TreeNode::single(6))),
                TreeNode::right(3, TreeNode::single(5)));

            res.max_path_sum(&r);
            println!("{}", res.max);
            assert_eq!(res.max, 21);
        }
        
        {
            res.max = 0;
            let r = TreeNode::full(
                1,
                TreeNode::full(
                    -2,
                    TreeNode::left(1, TreeNode::single(-1)),
                    TreeNode::single(3)),
                TreeNode::left(-3, TreeNode::single(-2)));

            res.max_path_sum(&r);
            println!("{}", res.max);
            assert_eq!(res.max, 3);
        }
    }
}
