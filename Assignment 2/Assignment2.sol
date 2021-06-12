// SPDX-License-Identifier: MIT
pragma solidity ^0.5.0;
import "github.com/OpenZeppelin/openzeppelin-contracts/blob/v2.5.0/contracts/math/SafeMath.sol";
// This is just a simple example of a coin-like contract.
// It is not standards compatible and cannot be expected to talk to other
// coin/token contracts. If you want to create a standards-compliant
// token, see: https://github.com/ConsenSys/Tokens. Cheers!

contract MetaCoin {
	mapping (address => uint256) balances;

	event Transfer(address indexed _from, address indexed _to, uint256 _value);

	constructor() public {
		balances[tx.origin] = 100000;
	}

	function sendCoin(address receiver, uint256 amount, address sender) public returns(bool sufficient) {
		if (balances[sender] < amount) return false;
		balances[sender] -= amount;
		balances[receiver] += amount;
		emit Transfer(sender, receiver, amount);
		return true;
	}


	function getBalance(address addr) public view returns(uint256) {
		return balances[addr];
	}
}

// Try not to edit the contract definition above

contract Loan is MetaCoin {
// You can edit this contract as much as you want. A template is provided here and you can change the function names and implement anything else you want, but the basic tasks mentioned here should be accomplished.
    mapping (address => uint256) private loans;
    address[] private key; 
    address private maxLoanAddress;
    event Request(address indexed _from, uint256 P, uint R, uint T, uint256 amt);
    
    address private Owner;

    
    modifier isOwner() {
        require(msg.sender==Owner);// Implement a modifier to allow only the owner of the contract to use specific functions
        _;
    }
    
    constructor() public {
        Owner=msg.sender; // Make the creator of the contract the Owner.
        // You can take the help of 2_owner.sol contract in remix for this and the above function. 
    }
    
    // Fill up the following function definitions and also try to justify why some functions are pure and some are view and some are none, in your README.md
    function mulDiv (uint x, uint y, uint z)
        public pure returns (uint)
        {
          uint a = x / z; uint b = x % z; // x = a * z + b
          uint c = y / z; uint d = y % z; // y = c * z + d
          return SafeMath.add(SafeMath.add(SafeMath.mul(SafeMath.mul(a , c), z), SafeMath.mul(a , d)), SafeMath.add(SafeMath.mul(b , c), SafeMath.mul(b , d) / z));
        }
    function getCompoundInterest(uint256 principal, uint rate, uint time) public pure returns(uint256) {
    	// Anyone should be able to use this function to calculate the amount of Compound interest for given P, R, T
        // Solidity does not have a good support for fixed point numbers so we input the rate as a uint
        // A common way to perform division to calculate such percentages is mentioned here: 
        // https://medium.com/coinmonks/math-in-solidity-part-4-compound-interest-512d9e13041b just read the periodic compounding part and
        // https://medium.com/coinmonks/math-in-solidity-part-3-percents-and-proportions-4db014e080b1 just read the towards full proportion part.
        // A good way to prevent overflows will be to typecast principle, rate and the big number divider suggested in the above blogs as uint256 variables, just use uint256 R = rate;
       while(time!=0){
           time--;
           principal = SafeMath.add (principal, mulDiv (rate, principal, 100));
       }
       return principal;
    } 
    
    function reqLoan(uint256 principal, uint rate, uint time) public returns(bool correct) {
        uint256 toPay = getCompoundInterest(principal, rate, time);
        
        if(toPay<principal) return false;
        // A creditor uses this function to request the Owner to settle his loan, and the amount to settle is calculated using the inputs.
        // Add appropriate definition below to store the loan request of a contract in the loans mapping,
        // Also emit the Request event after succesfully adding to the mapping, and return true. Return false if adding to the mapping failed (maybe the user entered a float rate, there were overflows and toPay comes to be lesser than principle, etc.
        key.push(msg.sender);
        if(toPay>loans[maxLoanAddress]){
            maxLoanAddress=msg.sender;
        }
        loans[msg.sender]+=toPay;
        emit Request(msg.sender, principal, rate, time, toPay);
        return true;
    }
    
    function getOwnerBalance() public view returns(uint256) {
				// use the getBalance function of MetaCoin contract to view the Balance of the contract Owner.
				// hint: how do you access the functions / variables of the parent class in your favorite programming language? It is similar to that in solidity as well!
				return super.getBalance(Owner);
		}
    
    
    // implement viewDues and settleDues which allow *ONLY* the owner to *view* and *settle* his loans respectively. They take in the address of a creditor as arguments. viewDues returns a uint256 corresponding to the due amount, and does not modify any state variables. settleDues returns a bool, true if the dues were settled and false otherwise. Remember to set the the pending loan to 0 after settling the dues.
    // use sendCoin function of MetaCoin contract to send the coins required for settling the dues.
    
    function viewDues(address _lender) public view isOwner returns(uint256){
        return loans[_lender];
    }
    
    function settleDues(address _lender) public isOwner returns(bool successful){
        successful=super.sendCoin(_lender, loans[_lender], Owner);
        if(successful) loans[_lender]=0;
    }
    
    function getMaxAddress() public view isOwner returns (address maxLoan){
        maxLoan=key[0];
        for(uint i=1;i<key.length;i++){
            if(loans[key[i]]>loans[maxLoan]){
                maxLoan=key[i];
            }
        }
    }
    function getMaxAddress2() public view isOwner returns (address ){
        return maxLoanAddress;
    }
    
}
