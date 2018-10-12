import React, { Component } from 'react';
import logo from './assets/logo.png';
import './App.css';
import 'semantic-ui-css/semantic.min.css';
import {Input, Image, Header, Button} from 'semantic-ui-react'

class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      expression: '',
      isVariable: false
    };
  }
  handleChange = async (e,data) => {

    const nGROKendpoint = 'http://127.0.0.1:8080/getresult';

    const rawResponse = await fetch(nGROKendpoint, { method: 'POST',
        headers: { 'content-type': 'text/plain' },
        body: data.value
      }
      );

    this.setState({
      expression: await rawResponse.text()
    });
    this.checkInput();
  }

  checkInput = () => {
    const {expression} = this.state;
    if(expression.length !== 0){
      this.setState({
        isVariable: expression[0].match(/[a-z]/i)
      });
    }
    else {
      this.setState({
        isVariable: false
      });
    }

  }
  render() {
    const { isVariable, expression }  = this.state;
    return (
      <div className="App">
        <header className="App-header">
          <div style={{paddingTop: 100, paddingBottom: 300}}>
            <Image size='small' centered src={logo} className="App-logo" alt="logo" />
            <p style={{paddingTop: 30, paddingBottom: 30}}>
            <code>Input an algebraic expression.</code>
          </p>{
            isVariable &&
            <div style={{paddingBottom: 20}}>
            <Button size="big" fluid color='yellow'>
              Add Variable
            </Button>
          </div>
          }
            <Input label='exp' onChange={this.handleChange} fluid size="medium" icon='calculator' placeholder='Numbers go here...' />
            <Header style={{paddingTop: 80, color: 'white'}} size='huge'>
              {expression}
            </Header>
        </div>
        </header>
      </div>
    );
  }
}

export default App;
