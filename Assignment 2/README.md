# SMART CONTRACT LOAN
This contract extends the functionality of the MetaCoin contract and acts as a loan deposit and settling contract.
- ## Constructor:
  When the contract is deployed from an address, the `Owner` of the contract is set as the address of the creator:   
    ```Owner=msg.sender;```
- ## getCompoundInterest:  
  ### Visibility-*Public* 
  Iterative implementation to calculate the final amount by taking `principal`, `rate` and `time` as `uint` inputs. 
  >Number of iterations: `time` 
   
  In each iteration, `principal` is updated to
  >`principal` + (`principal` * `rate`) / 100. 
  
  The second term in the above addition operation can cause a overflow. To prevent that, a helper function `muldiv` has been used.
  
    `muldiv` helps in evaluating the expression `xy/z` by breaking x and y into `az+b` and `cz+d` respectively. \
    So `xy/z` becomes `acz+ad+bc+bd/z`. 
  Further, overflow is checked by using the **SafeMath** library for addition and multiplication. 
  
  
  Sample input: \
             - `principal`=13313, `rate`=3, `time`=2 \
              - *returns 14123*
- ## reqLoan:
    ### Visibility-*Public* 
    When this function is called from an address, an amount `toPay` is calculated for the input `principal`, `rate` and `time` using the `getCompoundInterest` function. 
    > ```uint256 toPay = getCompoundInterest(principal, rate, time);```  
    
    The `loans` mapped to this address (the caller of this function) is increased by `toPay`. 
    > ```loans[msg.sender]+=toPay;``` 
    
    In case the mapping fails ( if `toPay` > `principal`), the function *returns* `false`, 
    else it *returns* `true` and the `Request` *event* is emitted.
- ## getOwnerBalance:
    ### Visibility-*Public* 
    The child contract `Loan` makes a call to the function **getBalance** in the parent contract `MetaCoin`, and returns the value received. 
    > ```return super.getBalance(Owner);```
 - ## viewDues:
      ### Visibility-*Public* 
      This function can only be called from the `Owner` address. In other cases, it will raise an error. \
      It simply returns the `loans` mapped to the input address (`_lender`).
      > ```return loans[_lender];```
 - ## settleDues:   
     ### Visibility-*Public* 
     This function can only be called from the `Owner` address. In other cases, it will raise an error. \
     It calls the function  **sendCoin** from the parent contract. If `sender`'s balance is less than the `amount` to be transferred, transaction fails, and the **sendCoin** function returns `false` which is
     stored in the variable `successful`.
      > ```successful=super.sendCoin(_lender, loans[_lender], Owner);```
      
     The `loans` mapped to the input address is set to 0 only if the transaction is successful.
     > ```if(successful) loans[_lender]=0;```
    
    
 ***   
## A Walkthrough Example
  - Open [Remix IDE](https://remix.ethereum.org/)
  - Copy the code from the file *Assignment2.sol* and paste it in a .sol file in Remix.
  - Deploy the contract **Loan** from the account with address, say `0x5B38Da6a701c568545dCfcB03FcB875f56beddC4`
  - Calling the **getOwnerBalance** function will return 100000.
  - Now, change the account to address, say `0xAb8483F64d9C6d1EcF9b849Ae677dD3315835cb2`, and call the function **reqLoan** with `principal`=13313, `rate`=3 and `time`=2.
  - Try to call the **viewDues** function from the same address with input as `0xAb8483F64d9C6d1EcF9b849Ae677dD3315835cb2`. Function call will fail, because caller is not the `Owner`
  - So, change the account back to address `0x5B38Da6a701c568545dCfcB03FcB875f56beddC4` (`Owner`), and call the **viewDues** function with input as `0xAb8483F64d9C6d1EcF9b849Ae677dD3315835cb2`.\
    The function will return 14123, hence proving that the **getCompoundInterest** and the **muldiv** functions are also working properly.
  - Now, call the function **settleDues** from the same account, with input as `0xAb8483F64d9C6d1EcF9b849Ae677dD3315835cb2`. Since 14123<100000, transaction will be successful.
  - To verify, that the transaction was successful, call **getOwnerBalance** function. It will return 85877. Also the **viewDues** function for input `0xAb8483F64d9C6d1EcF9b849Ae677dD3315835cb2` will now return 0.
  - In the above example, It can be verified that if the `principal` in the **reqLoan** function is changed to 927914, and the rest of the steps are followed in the same manner, the **settleDues** function will return false, because the amount will be greater than `Owner`'s balance. 
