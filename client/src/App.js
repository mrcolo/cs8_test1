import React, { Component } from 'react';
import logo from './assets/logo.png';
import './App.css';
import 'semantic-ui-css/semantic.min.css';
import {Input, Image, Header, Button, List, Icon} from 'semantic-ui-react'

class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      expression: '',
      isVariable: false,
      isDelete: false,
      isExport: false,
      isExiting: false,
      current_var:''
    };
  }

  handleAddVar = () => {
    alert("expression is now stored in memory location <M>")
  }

  handleDelVar = () => {
    alert("Now deleted expression in memory")
  }

  handleGetVar = () => {

    console.log("Getting expressions...")

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
    this.checkImport();
    this.checkExport();
    this.checkDelete();
    this.checkClose();
  }

  checkInput = () => {
    const { expression } = this.state;
    if(expression.length !== 0){
      this.setState({
        isVariable: expression[0].match(/[a-z]/i)
      });
    }
    else{
      this.setState({
        isVariable: false
      });
    }
  }

  checkClose = () => {
    const { expression } = this.state;

    if(expression.length >= 4 && expression.includes("exit")){
      this.setState({
        isExiting: expression.includes("exit"),
        isVariable: false
      });
    }
    else {
      this.setState({
        isExiting: false
      });
    }
  }

  checkDelete = () => {
    const {expression} = this.state;

    if(expression.length >= 5 && expression.includes("clear")){
      this.setState({
        isDelete: expression.includes("clear"),
        isVariable: false
      });
    }
    else {
      this.setState({
        isDelete: false
      });
    }
  }

  checkExport = () => {
    const {expression} = this.state;

    if(expression.length >= 6 && expression.includes("export")){
      this.setState({
        isExport: expression.includes("export"),
        isVariable: false
      });
    }
    else {
      this.setState({
        isExport: false
      });
    }
  }

  checkImport = () => {
    const {expression} = this.state;

    if(expression.length >= 6 && expression.includes("import")){
      this.setState({
        isImport: expression.includes("import"),
        isVariable: false
      });
    }
    else {
      this.setState({
        isImport: false
      });
    }
  }

  closeSession = () => {
    alert("I'm a web app! Just close the browser.")
  }

  render() {
    const { isVariable, isDelete, isExport, isImport, isExiting, expression }  = this.state;

    return (
      <div className="App">
        <header className="App-header">
          <div style={{paddingTop: 100, paddingBottom: 300}}>
            <Image size='small' centered src={logo} className="App-logo" alt="logo" />
            <p style={{paddingTop: 30, paddingBottom: 30}}>
            <code>Input an algebraic expression.</code>
          </p>
          {
            isVariable &&
            <div style={{paddingBottom: 20}}>
            <Button size="big" fluid color='yellow'>
              Add Variable
            </Button>
          </div>
          }
          {
            isDelete &&
            <div style={{paddingBottom: 20}}>
            <Button size="big" fluid color='red'>
              Delete Variable
            </Button>
          </div>
          }
          {
            isExport &&
            <div style={{paddingBottom: 20}}>
            <Button size="big" fluid color='green'>
              Export Session
            </Button>
          </div>
          }
          {
            isImport &&
            <div style={{paddingBottom: 20}}>
            <Button size="big" fluid color='blue'>
              Import Session
            </Button>
          </div>
          }
          {
            isExiting &&
            <div style={{paddingBottom: 20}}>
            <Button onClick={this.closeSession} size="big" fluid color='grey'>
              Exit
            </Button>
          </div>
          }
            <Input label='exp' onChange={this.handleChange} fluid size="medium" icon='calculator' placeholder='Numbers go here...' />
            {expression.length === 0 &&
              <div style={{paddingTop: 30}}>
                <List inverted size="small" animated verticalAlign='middle'>
                  <List.Item>
                    <Icon name='plus' size='large' />
                    <List.Content>
                      <List.Header>add expression: f = ...</List.Header>
                    </List.Content>
                  </List.Item>
                  <List.Item>
                    <Icon name='delete' size='large' />
                    <List.Content>
                      <List.Header>clear expression: clear f</List.Header>
                    </List.Content>
                  </List.Item>
                  <List.Item>
                    <Icon name='folder open outline' size='large' />
                    <List.Content>
                      <List.Header>import</List.Header>
                    </List.Content>
                  </List.Item>
                  <List.Item>
                    <Icon name='share' size='large' />
                    <List.Content>
                      <List.Header>export</List.Header>
                    </List.Content>
                  </List.Item>
                  <List.Item>
                    <Icon name='log out' size='large' />
                    <List.Content>
                      <List.Header>exit</List.Header>
                    </List.Content>
                  </List.Item>
                </List>
              </div>
            }
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
