import React, { Component } from 'react';
import logo from './assets/logo.png';
import './App.css';
import 'semantic-ui-css/semantic.min.css';
import {Input, Image, Header} from 'semantic-ui-react'

class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      expression: ''
    };
  }
  handleChange = async (e,data) => {

    const nGROKendpoint = 'http://localhost:8080/string';

    const rawResponse = await fetch(nGROKendpoint, { method: 'POST',
        url: 'http://localhost:8080',
        headers: { 'content-type': 'text/plain' },
        body: data.value
      }
      );
    this.setState({
      expression: await rawResponse.text()
    });
  }
  render() {
    const { expression }  = this.state;
    return (
      <div className="App">
        <header className="App-header">
          <div style={{paddingTop: 100, paddingBottom: 300}}>
            <Image size='small' centered src={logo} className="App-logo" alt="logo" />
            <p style={{paddingTop: 40, paddingBottom: 30}}>
            <code>Input an algebraic expression.</code>
            </p>
            <Input onChange={this.handleChange} fluid size="medium" icon='calculator' placeholder='Numbers go here...' />
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
